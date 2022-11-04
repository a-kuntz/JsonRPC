#ifndef X_RAY_SERVER_H
#define X_RAY_SERVER_H

#include <jsonrpc/rpc/Dispatcher.h>

#include <iostream>

namespace xray {

struct GetValue : public jsonrpc::rpc::IMethod;
struct SetValue : public jsonrpc::rpc::IMethod;
struct setTubeVoltage : public jsonrpc::rpc::IMethod;
struct setTubeCurrent : public jsonrpc::rpc::IMethod;
struct getStatus : public jsonrpc::rpc::IMethod;
struct takePicture : public jsonrpc::rpc::IMethod;
struct Status;

class Server
{
public:
	Server(io_context&..., port );

private:
	jsonrpc::rpc::Dispatcher dsp;
	Status status;
};
}
#endif /* X_RAY_SERVER_H */