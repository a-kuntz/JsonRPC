#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <setData.h>
#include <string>
using namespace jsonrpc;

class setData
{
private:
	bodyPart    part;
	patientData patient;
	double      energy;

public:
	bool flagPart    = false;
	bool flagPatient = false;
	bool flagEnergy  = false;
	struct BodyPart : public rpc::IMethod
	{
		rpc::Json call(const rpc::Json& data) override
		{
			part = data;
			flagPart = true;
			return "Bodypart has been set to" + std::to_string(part);
		}
	}

	struct PatientData : public rpc::IMethod
	{
		rpc ::Json call(const rpc::Json& data) override
		{
			//patient = data;
			flagPatient = true;
			return "patienData called";
		}
	}

	struct Intensity : public rpc::IMethod
	{
		rpc ::Json call(const rpc::Json& data) override
		{
			//energy = data;
			flagEnergy = true;
			return "Energy called";
		}
	}
};