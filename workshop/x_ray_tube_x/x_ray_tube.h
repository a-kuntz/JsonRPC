#ifndef SETDATA_H
#define SETDATA_H
#include <jsonrpc/rpc/Dispatcher.h>
#include <iostream>

class XRayTube
{
public:
	struct setTubeVoltage : public rpc::IMethod;
	struct setTubeCurrent : public rpc::IMethod;
	struct getStatus : public rpc::IMethod;
	struct takePicture : public rpc::IMethod;
private:
	double voltage;
	double current;
};

#endif /* SETDATA_H */