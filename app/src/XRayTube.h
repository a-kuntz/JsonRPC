#ifndef SETDATA_H
#define SETDATA_H
#include <jsonrpc/rpc/Dispatcher.h>
#include <jsonrpc/rpc/IMethod.h>
#include <iostream>

namespace xray {

class XRayTube
{
public:
	struct setTubeVoltage : public jsonrpc::rpc::IMethod;
	struct setTubeCurrent : public jsonrpc::rpc::IMethod;
	struct getStatus : public jsonrpc::rpc::IMethod;
	struct takePicture : public jsonrpc::rpc::IMethod;
private:
	double voltage;
	double current;
};
}
#endif /* SETDATA_H */