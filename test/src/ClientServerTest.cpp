#include <jsonrpc/Config.h>
#include <jsonrpc/net/ClientTransport.h>
#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Client.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <boost/asio.hpp>
#include <gtest/gtest.h>

#include <array>
#include <string>

class ClientServerTest : public ::testing::Test
{
protected:
	boost::asio::io_context _ioc;
	const int               _port = 55555;
	rpc::Dispatcher         _dispatcher;
	net::ServerTransport    _serverTransport;
	net::ClientTransport    _clientTransport;
	rpc::Client             _client;
	std::thread             _thread;

public:
	ClientServerTest()
		: _serverTransport(_ioc, _port, _dispatcher)
		, _clientTransport(_ioc)
		, _client(_clientTransport)
		, _thread([&]() { _ioc.run(); })
	{
		_clientTransport.connect("localhost", _port);
	}

	~ClientServerTest()
	{
		_ioc.stop();
		_thread.join();
	}

	rpc::Json call(const std::string& name, const std::string& params)
	{
		return _client.call(name, rpc::Json::parse(params));
	}

	rpc::Json expect(const std::string& s)
	{
		return rpc::Json::parse(s);
	}
};

namespace
{
struct Foo : public rpc::IMethod
{
	rpc::Json call(const rpc::Json& data) override
	{
		return "foo called";
	}
};

struct Bar : public rpc::IMethod
{
	rpc::Json call(const rpc::Json& data) override
	{
		return "bar called";
	}
};

} // namespace

TEST_F(ClientServerTest, FooBar)
{
	_dispatcher.add<Foo>("foo");
	_dispatcher.add<Bar>("bar");

	ASSERT_EQ(call("foo", R"(["arg1","arg2","arg3"])"), expect(R"("foo called")"));
	ASSERT_EQ(call("bar", R"("params")"), expect(R"("bar called")"));
	ASSERT_EQ(call("unknown method", R"("params")"), expect(R"({"code":-32601,"message":"Method not found"})"));
}

namespace
{

struct Substract : public rpc::IMethod
{
	rpc::Json call(const rpc::Json& params) override
	{
		int minuend    = 0;
		int subtrahend = 0;


		if (params.is_array())
		{
			std::array<int, 2> par = params;
			minuend                = par[0];
			subtrahend             = par[1];
		}
		else if (params.is_object())
		{
			minuend    = params.at("minuend");
			subtrahend = params.at("subtrahend");
		}


		return minuend - subtrahend;
	}
};

struct Notification : public rpc::IMethod
{
	rpc::Json call(const rpc::Json& params) override
	{
		return {};
	}
};

} // namespace

TEST_F(ClientServerTest, SpecificationExamples)
{
	_dispatcher.add<Substract>("subtract");
	_dispatcher.add<Notification>("update");
	_dispatcher.add<Notification>("foobar");

	// rpc call with positional parameters:
	// --> {"jsonrpc": "2.0", "method": "subtract", "params": [42, 23], "id": 1}
	// <-- {"jsonrpc": "2.0", "result": 19, "id": 1}
	ASSERT_EQ(
		call("subtract", R"([42, 23])"),
		expect(R"(19)"));

	// --> {"jsonrpc": "2.0", "method": "subtract", "params": [23, 42], "id": 2}
	// <-- {"jsonrpc": "2.0", "result": -19, "id": 2}
	ASSERT_EQ(
		call("subtract", R"([23, 42])"),
		expect(R"(-19)"));

	// rpc call with named parameters:
	// --> {"jsonrpc": "2.0", "method": "subtract", "params": {"subtrahend": 23, "minuend": 42}, "id": 3}
	// <-- {"jsonrpc": "2.0", "result": 19, "id": 3}
	ASSERT_EQ(
		call("subtract", R"({"subtrahend": 23, "minuend": 42})"),
		expect(R"(19)"));

	// --> {"jsonrpc": "2.0", "method": "subtract", "params": {"minuend": 42, "subtrahend": 23}, "id": 4}
	// <-- {"jsonrpc": "2.0", "result": 19, "id": 4}
	ASSERT_EQ(
		call("subtract", R"({"minuend": 42, "subtrahend": 23})"),
		expect(R"(19)"));

	// rpc call of non-existent method:
	// --> {"jsonrpc": "2.0", "method": "foobar", "id": "1"}
	// <-- {"jsonrpc": "2.0", "error": {"code": -32601, "message": "Method not found"}, "id": "1"}
	// renamed foobar -> foobar__ as foobar is needed in examples above
	ASSERT_EQ(
		call("foobar__", R"("")"),
		expect(R"({"code": -32601, "message": "Method not found"})"));

}