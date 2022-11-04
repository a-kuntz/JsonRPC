#include "XRayServer.h"

#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h

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
	SetValue(double& value) : _value(value) {}
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
	rpc::Json call(const rpc::Json& data) override
	{
		if (data.is_array())
		{
			std::array<double, 1> par = data;
			voltage                   = par[0];
		}
		else if (data.is_object())
		{
			voltage = data.at("voltage");
		}
		return "Tube Voltage has been set to" + voltage;
	}
}

struct xray::setTubeCurrent
{
	rpc ::Json call(const rpc::Json& data) override
	{
		if (data.is_array())
		{
			std::array<double, 1> par = data;
			current                   = par[0];
		}
		else if (data.is_object())
		{
			current = data.at("current");
		}
		return "Tube Current has been set to" + current;
	}
}

struct xray::getStatus
{
	rpc ::Json call(const rpc::Json& data) override
	{
		if (voltage == NULL)
		{
			return "Tube Voltage is not set."
		}
		else if (current == NULL)
		{
			return "Tube Current is not set."
		}
		else if (voltage == NULL && current == NULL)
		{
			return "Tube Current and Tube Voltage are not set."
		}
		else
		{
			return "Current settings are: Tube Voltage = " + voltage + " Tube Current = " + current;
		}
	}
}

struct xray::takePicture
{
	rpc ::Json call(const rpc::Json& data) override
	{
		return "Picture taken."
	}
}

struct xray::Status
{
	double value;
}

xray::Server::Server(io_context&..., port)
{
	dsp.add<SetValue>("set-value", status.value);
	dsp.add<GetValue>("get-value", status.value);
}

} // namespace xray