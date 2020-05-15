#ifndef HEADER_BA6F4438_955A_11EA_9437_784F43782D09
#define HEADER_BA6F4438_955A_11EA_9437_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/net/ITransport.h>
#include <jsonrpc/rpc/Json.h>
#include <jsonrpc/rpc/Request.h>
#include <jsonrpc/rpc/Response.h>
#include <jsonrpc/util/Util.h>

#include <iostream>

namespace rpc
{

class Client
{
private:
	net::ITransport& _transport;
	int              _id = 0;

public:
	Client(net::ITransport& transport)
		: _transport(transport)
	{}

	Json call(const std::string name, const Json& args)
	{
		auto rsp = call(Request{"2.0", name, args, std::to_string(++_id)});

		if (rsp.result)
		{
			return *rsp.result;
		}
		else if (rsp.error)
		{
			return *rsp.error;
		}

		throw std::logic_error("request without result and error");
	}

private:
	Response call(const Request& req)
	{
		Json jreq = req;
		auto sreq = jreq.dump();

		std::cout << util::ts() << " < " << sreq << std::endl;
		auto srsp = _transport.send(sreq);
		std::cout << util::ts() << " > " << srsp << std::endl;
		auto jrsp = Json::parse(srsp);
		return jrsp;
	}
};

} // namespace rpc

#endif // HEADER_BA6F4438_955A_11EA_9437_784F43782D09