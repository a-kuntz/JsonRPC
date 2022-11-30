#include "XRayServer.h"

#include <boost/asio.hpp>
#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <string>

using namespace jsonrpc;

xray::setTubeVoltage::setTubeVoltage(double& voltage)
	: _voltage(voltage)
{}
rpc::Json xray::setTubeVoltage::call(const rpc::Json& data) //override
{
	if (data > 0 && data <= 100)
	{
		_voltage = data;
		return true;
	}
	else
	{
		return false;
	}
}

xray::setTubeCurrent::setTubeCurrent(double& current)
	: _current(current)
{}
rpc ::Json xray::setTubeCurrent::call(const rpc::Json& data) //override
{
	if (data > 0 && data <= 100)
	{
		_current = data;
		return true;
	}
	else
	{
		return false;
	}
}

xray::getTubeConfig::getTubeConfig(double& voltage, double& current)
	: _voltage(voltage)
	, _current(current)
{}
rpc ::Json xray::getTubeConfig::call(const rpc::Json& data) //override
{

	std::map<std::string, double> config{
		{"Voltage", _voltage},
		{"Current", _current},
	};
	return config;
}

xray::takePicture::takePicture(double& value)
	: _value(value)
{}
rpc ::Json xray::takePicture::call(const rpc::Json& data) //override
{
	return "Picture taken.;
}

xray::Server::Server(boost::asio::io_context& io_context, int port)
	: transport(io_context, port, dsp)
{
	dsp.add<setTubeVoltage>("setTubeVoltage", config.voltage);
	dsp.add<setTubeCurrent>("setTubeCurrent", config.current);
	dsp.add<getTubeConfig>("getTubeConfig", config.voltage, config.current);
	dsp.add<takePicture>("takePicture", config.value);
};
