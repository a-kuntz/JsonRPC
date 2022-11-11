#ifndef X_RAY_SERVER_H
#define X_RAY_SERVER_H

#include <boost/asio.hpp>
#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <iostream>

namespace xray
{

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
struct getTubeConfig : public jsonrpc::rpc::IMethod
{
	getTubeConfig(double& voltage, double& current);
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
	double value   = 0;
	double voltage = 0;
	double current = 0;
};

class Server
{
public:
	Server(boost::asio::io_context& io_context, int port);

private:
	jsonrpc::rpc::Dispatcher      dsp;
	Status                        status;
	jsonrpc::net::ServerTransport transport;
};
} // namespace xray
#endif /* X_RAY_SERVER_H */
