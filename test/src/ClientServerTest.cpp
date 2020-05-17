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
		return _client.call(name, params);
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

TEST_F(ClientServerTest, FooBar_F)
{
	_dispatcher.add<Foo>("foo");
	_dispatcher.add<Bar>("bar");

	ASSERT_EQ(call("foo", R"(["arg1","arg2","arg3"])"), expect(R"("foo called")"));
	ASSERT_EQ(call("bar", R"(params)"), expect(R"("bar called")"));
	ASSERT_EQ(call("unknown method", R"(params)"), expect(R"({"code":-32601,"message":"Method not found"})"));
}
