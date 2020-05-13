#ifndef HEADER_F4C30FD1_9561_11EA_A786_784F43782D09
#define HEADER_F4C30FD1_9561_11EA_A786_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/net/IDispatcher.h>
#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Request.h>
#include <jsonrpc/rpc/Response.h>
#include <jsonrpc/util/Util.h>

// #include <chrono>
// #include <iomanip>
#include <iostream>

namespace rpc
{

class Dispatcher : public net::IDispatcher
{
public:
	std::string dispatch(const std::string& sreq) override
	{
		std::cout << util::ts() << " > " << sreq << std::endl;
		Request req  = Json::parse(sreq);
		auto    srsp = Json(dispatch(req)).dump();
		std::cout << util::ts() << " < " << srsp << std::endl;
		return srsp;
	};

private:
	Response dispatch(const Request& req)
	{
		return Response{"2.0", req.method, {}, req.id};
	}
};

} // namespace rpc

#endif // HEADER_F4C30FD1_9561_11EA_A786_784F43782D09
