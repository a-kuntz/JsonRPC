#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <deque>

using namespace boost;

template <typename ConnectionHandler>
class asio_generic_server
{
	using shared_handler_t = std::shared_ptr<ConnectionHandler>;

public:
	asio_generic_server(int thread_count = 1)
		: thread_count_(thread_count)
		, acceptor_(io_service_)
	{}
	void start_server(uint16_t port)
	{
		auto handler = std::make_shared<ConnectionHandler>(io_service_);
		// set up the acceptor to listen on the tcp port
		asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
		acceptor_.open(endpoint.protocol());
		acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
		acceptor_.bind(endpoint);
		acceptor_.listen();

		acceptor_.async_accept(handler->socket(), [=](auto ec) { handle_new_connection(handler, ec); });

		// start pool of threads to process the asio events
		for (int i = 0; i < thread_count_; ++i)
		{
			thread_pool_.emplace_back([=] { io_service_.run(); });
		}
	}

private:
	void handle_new_connection(shared_handler_t handler, system::error_code const& error)
	{
		if (error)
		{
			return;
		}
		handler->start();

		auto new_handler = std::make_shared<ConnectionHandler>(io_service_);
		acceptor_.async_accept(new_handler->socket(), [=](auto ec) { handle_new_connection(new_handler, ec); });
	}

	int                      thread_count_;
	std::vector<std::thread> thread_pool_;
	asio::io_service         io_service_;
	asio::ip::tcp::acceptor  acceptor_;
};

class chat_handler : public std::enable_shared_from_this<chat_handler>
{
public:
	chat_handler(asio::io_service& service)
		: service_(service)
		, socket_(service)
		, write_strand_(service)
	{}
	boost::asio::ip::tcp::socket& socket()
	{
		return socket_;
	}
	void start()
	{
		read_packet();
	}
	void read_packet()
	{
		asio::async_read_until(
			socket_, in_packet_, 0x00, [me = shared_from_this()](system::error_code const& ec, std::size_t bytes_xfer) {
				me->read_packet_done(ec, bytes_xfer);
			});
	}
	void read_packet_done(system::error_code const& error, std::size_t bytes_transferred)
	{
		if (error)
		{
			return;
		}
		std::istream stream(&in_packet_);
		std::string  packet_string;
		stream >> packet_string;
		// do something with it
		read_packet();
	}
	void send(std::string msg)
	{
		service_.post(write_strand_.wrap([me = shared_from_this(), msg]() { me->queue_message(msg); }));
	}

private:
	void queue_message(std::string message)
	{
		bool write_in_progress = !send_packet_queue.empty();
		send_packet_queue.push_back(std::move(message));
		if (!write_in_progress)
		{
			start_packet_send();
		}
	}
	void start_packet_send()
	{
		send_packet_queue.front() += "\0";
		async_write(
			socket_, asio::buffer(send_packet_queue.front()),
			write_strand_.wrap(
				[me = shared_from_this()](system::error_code const& ec, std::size_t) { me->packet_send_done(ec); }));
	}
	void packet_send_done(system::error_code const& error)
	{
		if (!error)
		{
			send_packet_queue.pop_front();
			if (!send_packet_queue.empty())
			{
				start_packet_send();
			}
		}
	}

	asio::io_service&        service_;
	asio::ip::tcp::socket    socket_;
	asio::io_service::strand write_strand_;
	asio::streambuf          in_packet_;
	std::deque<std::string>  send_packet_queue;
};

int main()
{
	asio_generic_server<chat_handler> server;
	server.start_server(8888);
	return 0;
}