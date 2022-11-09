#include "XRayServer.h"

#include <boost/asio.hpp>
#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <string>

using namespace jsonrpc;

xray::getValue::getValue(double& value)
	: _value(value)
{}
rpc::Json xray::getValue::call(const rpc::Json& data) //override
{
	return _value;
}

xray::setValue::setValue(double& value)
	: _value(value)
{}
rpc::Json xray::setValue::call(const rpc::Json& data) //override
{
	_value = data;
	return {};
}

xray::setTubeVoltage::setTubeVoltage(double& voltage)
	: _voltage(voltage)
{}
rpc::Json xray::setTubeVoltage::call(const rpc::Json& data) //override
{
	_voltage = data;
	return "Tube Voltage has been set to " + std::to_string(_voltage);
}

xray::setTubeCurrent::setTubeCurrent(double& current)
	: _current(current)
{}
rpc ::Json xray::setTubeCurrent::call(const rpc::Json& data) //override
{
	_current = data;
	return "Tube Current has been set to " + std::to_string(_current);
}

xray::getStatus::getStatus(double& voltage, double& current)
	: _voltage(voltage)
	, _current(current)
{}
rpc ::Json xray::getStatus::call(const rpc::Json& data) //override
{
	if (_voltage == 0 || _current == 0)
	{
		return "Tube Current or Tube Voltage are not set.";
	}
	else
	{
		return "Current settings are: Tube Voltage = " + std::to_string(_voltage)
			   + " Tube Current = " + std::to_string(_current);
	}
}

xray::takePicture::takePicture(double& value)
	: _value(value)
{}
rpc ::Json xray::takePicture::call(const rpc::Json& data) //override
{
	return "Picture taken.";
}

xray::Server::Server(boost::asio::io_context& io_context, int port)
 : transport(io_context, port, dsp)
{
	dsp.add<setValue>("set-value", status.value);
	dsp.add<getValue>("get-value", status.value);
	dsp.add<setTubeVoltage>("setTubeVoltage", status.voltage);
	dsp.add<setTubeCurrent>("setTubeCurrent", status.current);
	dsp.add<getStatus>("getStatus", status.voltage, status.current);
	dsp.add<takePicture>("takePicture", status.value);
};
