#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Json.h>
#include <jsonrpc/rpc/Request.h>
#include <jsonrpc/rpc/Response.h>
#include <jsonrpc/util/Util.h>

#include <boost/asio.hpp>
#include <fmt/format.h>

#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <variant>

using boost::asio::ip::tcp;
using namespace jsonrpc;
using namespace jsonrpc::rpc;

using ResponseType = std::variant<Json, Error>;
//using ResponseType = Json;
using Completion = std::function<void(const ResponseType&)>;
using IdType     = Json;
using Dispatcher = std::map<IdType, Completion>;

std::ostream& operator<<(std::ostream& out, const Completion& data)
{
	return out << "Cpl";
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& data) {
    std::copy(std::begin(data), std::end(data), std::ostream_iterator<T>(out, "\n"));
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::map<T, U>& data)
{
	//std::copy(std::begin(data), std::end(data), std::ostream_iterator<T>(out, "\n"));
	std::for_each(std::begin(data), std::end(data), [&out](const std::pair<const T, U>& element) {
		out << element.first << ":" << element.second << std::endl;
	});
	return out;
}

class Session : public std::enable_shared_from_this<Session>
{
private:
	tcp::socket& _socket;
	std::string  _buffer;

public:
	Session(boost::asio::io_context& ioc, tcp::socket& socket)
		: _socket(socket)
	{}

	IdType call(const std::string& name, const Json& args, const Dispatcher& dispatcher)
	{
		static int idVal = 0;

		IdType id = std::to_string(++idVal);

		// todo:: schedule timeout

		_buffer = Json(Request{"2.0", name, args, id}).dump();

		auto self(shared_from_this());

		boost::asio::async_write(
			_socket, boost::asio::buffer(_buffer),
			[this, self, &dispatcher](boost::system::error_code ec, std::size_t length) {
				if (!ec)
				{
					std::cout << fmt::format("{} <<< {} length={}\n", util::ts(), _buffer, length);

					receive(dispatcher);
				}
				else
				{
					std::cerr << "error on call: " << _buffer << " code: " << ec << " length: " << length << std::endl;
				}
			});
		return id;
	}

private:
	void receive(const Dispatcher& dispatcher)
	{
		auto self(shared_from_this());

		_buffer = "";

		boost::asio::async_read(
			_socket, boost::asio::dynamic_buffer(_buffer), boost::asio::transfer_at_least(1),
			[this, self, &dispatcher](boost::system::error_code ec, std::size_t /*length*/) {
				if (!ec)
				{
					util::for_each_split(_buffer, "}{", [&](const std::string& srsp) {
						std::cout << fmt::format("{} >>> {}\n", util::ts(), srsp);

						auto rsp = Response(Json::parse(srsp));
						if (rsp.id == Json({}))
						{
							throw std::runtime_error("invalid id: " + rsp.id.dump());
						}

						auto it = dispatcher.find(rsp.id);
						if (it == dispatcher.end())
						{
							throw std::runtime_error("invalid id: " + rsp.id.dump());
						}
						auto completion = it->second;

						if (rsp.result)
						{
							completion(*rsp.result);
						}
						else if (rsp.error)
						{
							completion(*rsp.error);
						}
					});
				}
			});
	}
};

class Client
{
private:
	boost::asio::io_context& _ioc;
	tcp::socket              _socket;
	Dispatcher               _dispatcher;

public:
	Client(boost::asio::io_context& ioc, const tcp::resolver::results_type& endpoints)
		: _ioc(ioc)
		, _socket(ioc)
	{
		boost::asio::async_connect(_socket, endpoints, [](boost::system::error_code ec, tcp::endpoint endpoint) {
			if (ec)
			{
				std::cerr << "error on connect to " << endpoint << " : " << ec << std::endl;
			}
		});
	}

	~Client()
	{
		close();
	}

	void call(const std::string& name, const Json& args, Completion completion)
	{
		auto session = std::make_shared<Session>(_ioc, _socket);
		auto id      = session->call(name, args, _dispatcher);
		_dispatcher.emplace(id, completion);
	}

	void close()
	{
		boost::asio::post(_ioc, [this]() { _socket.close(); });
	}
};

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << fmt::format("Usage: {} <host> <port>\n", argv[0]);
			return 1;
		}

		boost::asio::io_context io_context;

		tcp::resolver resolver(io_context);
		auto          endpoints = resolver.resolve(argv[1], argv[2]);

		// std::thread t([&io_context]() { io_context.run(); });
		auto ResponsePrinter = [](const ResponseType& rsp) {
			std::string res = std::holds_alternative<Error>(rsp) ? to_string(std::get<Error>(rsp))
																 : std::get<Json>(rsp).dump();
			std::cout << res << std::endl;
		};

		auto client = Client(io_context, endpoints);
		client.call("foo", Json::parse(R"([42, 23])"), ResponsePrinter);
		client.call("bar", Json::parse(R"("params")"), ResponsePrinter);
		client.call("unknown method", Json(), ResponsePrinter);

		io_context.run();
		// t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
