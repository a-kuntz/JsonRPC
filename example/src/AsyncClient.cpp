#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Json.h>
#include <jsonrpc/rpc/Request.h>
#include <jsonrpc/rpc/Response.h>
#include <jsonrpc/util/Util.h>

#include <boost/asio.hpp>
#include <fmt/format.h>

#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

using boost::asio::ip::tcp;
using namespace jsonrpc;
using namespace jsonrpc::rpc;

class Client : public std::enable_shared_from_this<Client>
{
private:
	boost::asio::io_context& _ioc;
	tcp::socket              _socket;
	std::string              _data;
	int                      _id;

public:
	using ResultType = Json;
	using Completion = std::function<void(const ResultType&)>;

	Client(boost::asio::io_context& ioc, const tcp::resolver::results_type& endpoints)
		: _ioc(ioc)
		, _socket(ioc)
	{
		boost::asio::async_connect(_socket, endpoints, [this](boost::system::error_code ec, tcp::endpoint) {
			if (ec)
			{
				std::cerr << "error on connect: " << ec << std::endl;
			}
		});
	}

	void call(const std::string& name, const Json& args, Completion completion)
	{
		std::string req = Json(Request{"2.0", name, args, std::to_string(++_id)}).dump();

		auto self(shared_from_this());

		boost::asio::async_write(
			_socket, boost::asio::buffer(req),
			[this, self, completion, req](boost::system::error_code ec, std::size_t length) {
				if (!ec)
				{
					std::cout << util::ts() << fmt::format(" <<< {}\n", req);

					receive(completion);
				}
				else
				{
					std::cerr << "error on call: " << req << " code: " << ec << " length: " << length << std::endl;
				}
			});
	}

	void close()
	{
		boost::asio::post(_ioc, [this]() { _socket.close(); });
	}

private:
	void receive(Completion completion)
	{
		auto self(shared_from_this());

		_data = "";

		boost::asio::async_read(
			_socket, boost::asio::dynamic_buffer(_data), boost::asio::transfer_at_least(1),
			[this, self, completion](boost::system::error_code ec, std::size_t /*length*/) {
				if (!ec)
				{
					auto srsp = _data;
					std::cout << util::ts() << " >>> " << srsp << std::endl;

					auto rsp = Response(Json::parse(srsp));

					if (rsp.result)
					{
						completion(Json(*rsp.result));
					}
					else if (rsp.error)
					{
						completion(Json(*rsp.error));
					}
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

		client->call("foo", Json::parse(R"([42, 23])"), [](const Client::ResultType& res) {
			std::cout << "res=" << res << std::endl;
		});

		// client->call("bar", Json::parse(R"("params")"), [](const Client::ResultType& res) {
		// 	std::cout << "res=" << res << std::endl;
		// });

		// client->call("unknown method", Json(), [](const Client::ResultType& res) {
		// 	std::cout << "res=" << res << std::endl;
		// });

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
