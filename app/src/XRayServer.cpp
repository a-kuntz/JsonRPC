#include "XRayServer.h"


#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <string>

using namespace jsonrpc;

namespace xray
{

struct xray::GetValue
{
	GetValue(double& value)
		: _value(value)
	{}
	rpc::Json call(const rpc::Json& data) override
	{
		return _value;
	}

private:
	double& _value;
};

struct xray::SetValue
{
	SetValue(double& value)
		: _value(value)
	{}
	rpc::Json call(const rpc::Json& data) override
	{
		_value = data;
		return {};
	}

private:
	double& _value;
};

struct xray::setTubeVoltage
{
	setTubeVoltage(double& voltage)
		: _voltage(voltage)
	{}
	rpc::Json call(const rpc::Json& data) override
	{
		_voltage = data;
		return "Tube Voltage has been set to" + _voltage;
	}

private:
	double& _voltage;
}

struct xray::setTubeCurrent
{
	setTubeCurrent(double& current)
		: _current(current)
	{}
	rpc ::Json call(const rpc::Json& data) override
	{
		_current = data;
		return "Tube Current has been set to" + _current;
	}

private:
	double& _current;
}

struct xray::getStatus
{
	getStatus(double& voltage, double& current)
		: _voltage(voltage)
		, _current(current)
	{}
	rpc ::Json call(const rpc::Json& data) override
	{
		if (_voltage == NULL || _current == NULL)
		{
			return "Tube Current or Tube Voltage are not set."
		}
		else
		{
			return "Current settings are: Tube Voltage = " + _voltage + " Tube Current = " + _current;
		}
	}

private:
	double& _voltage;
	double& _current;
}

struct xray::takePicture
{
	takePicture(double& value)
		: _value(value)
	{}
	rpc ::Json call(const rpc::Json& data) override
	{
		return "Picture taken."
	}

private:
	double& _value;
}

struct xray::Status
{
	double value;
	double voltage;
	double current;
}

xray::Server::Server(io_context&..., port)
{
	dsp.add<SetValue>("set-value", status.value);
	dsp.add<GetValue>("get-value", status.value);
	dsp.add<setTubeVoltage>("setTubeVoltage", status.voltage);
	dsp.add<setTubeCurrent>("setTubeCurrent", status.current);
	dsp.add<getStatus>("getStaus", status.voltage, status.current);
	dsp.add<takePicture>("takePicture", status.value);
	net::ServerTransport st(io_context, port, dsp);
}

} // namespace xray