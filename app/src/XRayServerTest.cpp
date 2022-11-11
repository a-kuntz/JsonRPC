#include "XRayServer.h"

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

class XRayServerTest : public ::testing::Test
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
	XRayServerTest()
		: _serverTransport(_ioc, _port, _dispatcher)
		, _clientTransport(_ioc)
		, _client(_clientTransport)
		, _thread([&]() { _ioc.run(); })
	{
		_clientTransport.connect("localhost", _port);
	}

	~XRayServerTest()
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
};

TEST_F(XRayServerTest, Workshop)
{
	xray::Status status;

	_dispatcher.add<xray::setTubeVoltage>("setTubeVoltage", status.voltage);
	_dispatcher.add<xray::setTubeCurrent>("setTubeCurrent", status.current);
	_dispatcher.add<xray::getTubeConfig>("getTubeConfig", status.voltage, status.current);
	_dispatcher.add<xray::takePicture>("takePicture", status.value);

	ASSERT_EQ(call("setTubeVoltage", "42.1"), expect(R"(true)"));
	ASSERT_EQ(call("setTubeCurrent", "22.4"), expect(R"(true)"));
	ASSERT_EQ(call("getTubeConfig", R"({})"), expect(R"("Current settings are: Tube Voltage = Tube Current = ")"));
	ASSERT_EQ(call("takePicture", R"({})"), expect(R"("Picture taken.")"));
}
