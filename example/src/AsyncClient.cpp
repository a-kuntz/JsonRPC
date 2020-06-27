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
using Completion   = std::function<void(const ResponseType&)>;
using IdType       = Json;

std::ostream& operator<<(std::ostream& out, const Completion& data)
{
	return out << "Cpl";
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& data)
{
	std::copy(std::begin(data), std::end(data), std::ostream_iterator<T>(out, "\n"));
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::map<T, U>& data)
{
	std::for_each(std::begin(data), std::end(data), [&out](const std::pair<const T, U>& element) {
		out << element.first << ":" << element.second << std::endl;
	});
	return out;
}

class CompletionMap
{
public:
	auto emplace(const IdType& id, const Completion& completion)
	{
		return _map.emplace(id, completion);
	}
	Completion release(const IdType& id)
	{
		auto it = _map.find(id);
		if (it == _map.end())
		{
			throw std::runtime_error("invalid id: " + id.dump());
		}

		Completion cpl = it->second;

		_map.erase(it);
		return cpl;
	}
	bool empty()
	{
		return _map.empty();
	}

private:
	std::map<IdType, Completion> _map;
};

class Session : public std::enable_shared_from_this<Session>
{
private:
	boost::asio::io_context& _ioc;
	tcp::socket&             _socket;
	CompletionMap&           _map;
	std::string              _buffer;

public:
	Session(boost::asio::io_context& ioc, tcp::socket& socket, CompletionMap& map)
		: _ioc(ioc)
		, _socket(socket)
		, _map(map)
	{}

	void call(const std::string& name, const Json& args, Completion completion)
	{
		static int idVal = 0;

		IdType id = std::to_string(++idVal);

		// todo:: schedule timeout

		_buffer = Json(Request{"2.0", name, args, id}).dump();

		auto self(shared_from_this());

		boost::asio::async_write(
			_socket, boost::asio::buffer(_buffer), [this, self](boost::system::error_code ec, std::size_t length) {
				if (!ec)
				{
					std::cout << fmt::format("{} <<< {} length={}\n", util::ts(), _buffer, length);

					receive();
				}
				else
				{
					std::cerr << "error on call: " << _buffer << " code: " << ec << " length: " << length << std::endl;
				}
			});

		_map.emplace(id, completion);
	}

private:
	void receive()
	{
		auto self(shared_from_this());

		_buffer = "";

		boost::asio::async_read(
			_socket, boost::asio::dynamic_buffer(_buffer), boost::asio::transfer_at_least(1),
			[this, self](boost::system::error_code ec, std::size_t /*length*/) {
				if (!ec)
				{
					util::for_each_split(_buffer, "}{", [&](const std::string& srsp) {
						std::cout << fmt::format("{} >>> {}\n", util::ts(), srsp);

						auto rsp = Response(Json::parse(srsp));
						if (rsp.id == Json({}))
						{
							throw std::runtime_error("invalid id: " + rsp.id.dump());
						}

						auto completion = _map.release(rsp.id);

						if (rsp.result)
						{
							completion(*rsp.result);
						}
						else if (rsp.error)
						{
							completion(*rsp.error);
						}

						if (_map.empty())
						{
							close();
						}
					});
				}
			});
	}
	void close()
	{
		auto self(shared_from_this());
		boost::asio::post(_ioc, [this, self]() { _socket.close(); });
	}
};

class Client
{
private:
	boost::asio::io_context& _ioc;
	tcp::socket              _socket;
	CompletionMap            _map;

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
		auto session = std::make_shared<Session>(_ioc, _socket, _map);
		session->call(name, args, completion);
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

		boost::asio::io_context ioc;

		auto resolver  = tcp::resolver(ioc);
		auto endpoints = resolver.resolve(argv[1], argv[2]);

		auto ResponsePrinter = [&](const ResponseType& rsp) {
			std::string res =
				std::holds_alternative<Error>(rsp) ? to_string(std::get<Error>(rsp)) : std::get<Json>(rsp).dump();
			std::cout << res << std::endl;
		};

		auto client = Client(ioc, endpoints);
		client.call("foo", Json::parse(R"([42, 23])"), ResponsePrinter);
		client.call("bar", Json::parse(R"("params")"), ResponsePrinter);
		client.call("unknown method", Json(), ResponsePrinter);

		ioc.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
