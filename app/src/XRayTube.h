#ifndef SETDATA_H
#define SETDATA_H
#include <jsonrpc/rpc/Dispatcher.h>
#include <jsonrpc/rpc/IMethod.h>
#include <iostream>

namespace xray {

struct setTubeVoltage : public jsonrpc::rpc::IMethod;
struct setTubeCurrent : public jsonrpc::rpc::IMethod;
struct getStatus : public jsonrpc::rpc::IMethod;
struct takePicture : public jsonrpc::rpc::IMethod;

struct SetValue : public rpc::IMethod
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

struct GetValue : public rpc::IMethod
{
	GetValue(double& value) : _value(value) {}
	rpc::Json call(const rpc::Json& data) override
	{
		return _value;
	}
	private:
	double& _value;
};


struct Status
{
	double value;
}

class Server
{
public:
	Server(io_context&..., port ) {
		dsp.add<SetValue>("set-value", status.value);
		dsp.add<GetValue>("get-value", status.value);
	}

private:
	rpc::Dispatcher dsp;
	Status status;
};
}
#endif /* SETDATA_H */