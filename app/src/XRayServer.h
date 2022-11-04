#ifndef X_RAY_SERVER_H
#define X_RAY_SERVER_H

#include <boost/asio.hpp>
#include <jsonrpc/rpc/Dispatcher.h>

#include <iostream>

namespace xray
{

struct getValue : public jsonrpc::rpc::IMethod
{
	getValue(double& value);
	jsonrpc::rpc::Json call(const jsonrpc::rpc::Json& data);

private:
	double& _value;
};
struct setValue : public jsonrpc::rpc::IMethod
{
	setValue(double& value);
	jsonrpc::rpc::Json call(const jsonrpc::rpc::Json& data);

private:
	double& _value;
};
struct setTubeVoltage : public jsonrpc::rpc::IMethod
{
	setTubeVoltage(double& voltage);
	jsonrpc::rpc::Json call(const jsonrpc::rpc::Json& data);

private:
	double& _voltage;
};
struct setTubeCurrent : public jsonrpc::rpc::IMethod
{
	setTubeCurrent(double& current);
	jsonrpc::rpc::Json call(const jsonrpc::rpc::Json& data);

private:
	double& _current;
};
struct getStatus : public jsonrpc::rpc::IMethod
{
	getStatus(double& voltage, double& current);
	jsonrpc::rpc::Json call(const jsonrpc::rpc::Json& data);

private:
	double& _voltage;
	double& _current;
};
struct takePicture : public jsonrpc::rpc::IMethod
{
	takePicture(double& value);
	jsonrpc::rpc::Json call(const jsonrpc::rpc::Json& data);

private:
	double& _value;
};
struct Status
{
	double value;
	double voltage;
	double current;
};

class Server
{
public:
	Server();
	//Server(boost::asio::io_context& io_context, int port);

private:
	jsonrpc::rpc::Dispatcher dsp;
	Status                   status;
};
} // namespace xray
#endif /* X_RAY_SERVER_H */