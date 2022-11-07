#include "app/src/XRayServer.h"

#include <jsonrpc/Config.h>
#include <jsonrpc/net/ClientTransport.h>
#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Client.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <boost/asio.hpp>
#include <gtest/gtest.h>

#include <array>
#include <chrono>
#include <random>
#include <string>
#include <thread>

using namespace std::chrono_literals;
using namespace jsonrpc;

class ServerClientTest : public ::testing::test
{
protected:
	boost::asio::io_context    _ioc;
	static inline std::mt19937 _random_engine{std::random_device{}()};
	static inline int          _port = std::uniform_int_distribution<int>{2000, 9000}(_random_engine);
	rpc::Dispatcher            _dispatcher;
	net::ServerTransport       _serverTransport;
	net::ClientTransport       _clientTransport;
	rpc::Client                _client;
	std::thread                _thread;

public:
	ServerClientTest()
		: _serverTransport(_ioc, _port, _dispatcher)
		, _clientTransport(_ioc)
		, _client(_clientTransport)
		, _thread([&]() { _ioc.run(); })
	{
		_clientTransport.connect("localhost", _port);
	}

	~ServerClientTest()
	{
		_ioc.stop();
		_thread.join();
	}

	void notify(const std::string& name, const std::string& params)
	{
		_client.notify(name, params);
	}

	rpc::Json call(const std::string& name, const std::string& params)
	{
		return _client.call(name, rpc::Json::parse(params));
	}

	rpc::Json expect(const std::string& s)
	{
		return rpc::Json::parse(s);
	}
}

TEST_F(ClientServerTest, Workshop)
{
	_dispatcher.add<xray::setTubeVoltage>("setTubeVoltage");
	_dispatcher.add<xray::setTubeCurrent>("setTubeCurrent");
	_dispatcher.add<xray::getStatus>("getStatus");
	_dispatcher.add<xray::takePicture>("takePicture");

	ASSERT_EQ(call("setTubeVoltage", R"([42.1])"), expect(R"(Tube Voltage has been set to 42.1)"));
	ASSERT_EQ(call("setTubeCurrent", R"([22.4])"), expect(R"(Tube Current has been set to 22.4)"));
	ASSERT_EQ(call("getStatus", R"([{},{}])"), expect(R"(Tube Current or Tube Voltage are not set.)"));
	ASSERT_EQ(call("setTubeCurrent", R"([{}])"), expect(R"(Picture taken.)"));
}
