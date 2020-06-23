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

using ResultType = Json;
using Completion = std::function<void(const ResultType&)>;

class Session : public std::enable_shared_from_this<Session>
{
private:
	boost::asio::io_context& _ioc;
	tcp::socket              _socket;
	std::string              _buffer;

public:

	Session(boost::asio::io_context& ioc, const tcp::resolver::results_type& endpoints)
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

	~Session()
    {
	    close();
    }

	void call(const std::string& name, const Json& args, Completion completion)
	{
		static int id = 0;

        _buffer = Json(Request{"2.0", name, args, std::to_string(++id)}).dump();

		auto self(shared_from_this());

		boost::asio::async_write(
			_socket, boost::asio::buffer(_buffer),
			[this, self, completion](boost::system::error_code ec, std::size_t length) {
				if (!ec)
				{
					std::cout << fmt::format("{} <<< {} length={}\n", util::ts(), _buffer, length);

					receive(completion);
				}
				else
				{
					std::cerr << "error on call: " << _buffer << " code: " << ec << " length: " << length << std::endl;
				}
			});
	}

private:
	void close()
	{
		boost::asio::post(_ioc, [this]() { _socket.close(); });
	}

	void receive(Completion completion)
	{
		auto self(shared_from_this());

        _buffer = "";

		boost::asio::async_read(
                _socket, boost::asio::dynamic_buffer(_buffer), boost::asio::transfer_at_least(1),
                [this, self, completion](boost::system::error_code ec, std::size_t /*length*/) {
				if (!ec)
				{
					auto srsp = _buffer;
					std::cout << fmt::format("{} >>> {}\n", util::ts(), srsp);

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

class Client
{
private:
    boost::asio::io_context& _ioc;
    const tcp::resolver::results_type& _endpoints;
public:
    Client(boost::asio::io_context& ioc, const tcp::resolver::results_type& endpoints)
    : _ioc(ioc)
    , _endpoints(endpoints)
    {}
    void call(const std::string& name, const Json& args, Completion completion)
    {
        auto session = std::make_shared<Session>(_ioc, _endpoints);
        session->call(name, args, completion);
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

		auto client = Client(io_context, endpoints);
		client.call("foo", Json::parse(R"([42, 23])"), [](const ResultType& res) {
			std::cout << fmt::format("res={}\n", res);
		});

		// todo: reuse socket
		client.call("bar", Json::parse(R"("params")"), [](const ResultType& res) {
			std::cout << fmt::format("res={}\n", res);
		});

		client.call(
			"unknown method", Json(), [](const ResultType& res) { std::cout << fmt::format("res={}\n", res); });

		io_context.run();
		// t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
