#include <jsonrpc/Config.h>
// #include <jsonrpc/net/async/ClientTransport.h>
// #include <jsonrpc/rpc/async/Client.h>

#include <boost/asio.hpp>

#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

using boost::asio::ip::tcp;
using namespace jsonrpc;

class Client : public std::enable_shared_from_this<Client>
{
private:
	boost::asio::io_context& _ioc;
	tcp::socket              _socket;
	std::string              _data;

public:
	using Completion = std::function<void(const std::string&)>;

	Client(boost::asio::io_context& ioc, const tcp::resolver::results_type& endpoints)
		: _ioc(ioc)
		, _socket(ioc)
	{
		doConnect(endpoints);
	}

	void send(const std::string& request, Completion completion)
	{
		auto self(shared_from_this());

		boost::asio::async_write(
			_socket, boost::asio::buffer(request),
			[this, self, completion, request](boost::system::error_code ec, std::size_t length) {
				if (!ec)
				{
					std::cout << "< " << request << std::endl;
					asyncRead(completion);
				}
				else
				{
					std::cerr << "error on send: " << request << " code: " << ec << " length: " << length << std::endl;
				}
			});
	}

	void close()
	{
		boost::asio::post(_ioc, [this]() { _socket.close(); });
	}

private:
	void doConnect(const tcp::resolver::results_type& endpoints)
	{
		boost::asio::async_connect(_socket, endpoints, [this](boost::system::error_code ec, tcp::endpoint) {
			if (ec)
			{
				std::cerr << "error on connect: " << ec << std::endl;
			}
		});
	}

	void asyncRead(Completion completion)
	{
		auto self(shared_from_this());

		_data = "";

		boost::asio::async_read(
			_socket, boost::asio::dynamic_buffer(_data), boost::asio::transfer_at_least(1),
			[this, self, completion](boost::system::error_code ec, std::size_t /*length*/) {
				if (!ec)
				{
					std::cout << "> " << _data << std::endl;
					completion(_data);
				}
			});
	}
};

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: " << argv[0] << " <host> <port>\n";
			return 1;
		}

		boost::asio::io_context io_context;

		tcp::resolver resolver(io_context);
		auto          endpoints = resolver.resolve(argv[1], argv[2]);
		auto          client    = std::make_shared<Client>(io_context, endpoints);

		// std::thread t([&io_context]() { io_context.run(); });

		client->send(R"({"jsonrpc": "2.0", "method": "foo", "params": [42, 23], "id": 1})", [](const std::string& res) {
			std::cout << "res=" << res << std::endl;
		});

		// net::async::ClientTransport transport(io_context);
		// transport.connect(argv[1], atoi(argv[2]));

		// auto client = rpc::async::Client(transport);
		// client.call("foo", {"arg1", "arg2", "arg3"});
		// client.call("bar", "params");
		// client.call("unknown method", {});

		io_context.run();
		client->close();
		// t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
