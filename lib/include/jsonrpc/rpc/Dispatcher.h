#ifndef HEADER_F4C30FD1_9561_11EA_A786_784F43782D09
#define HEADER_F4C30FD1_9561_11EA_A786_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/net/IDispatcher.h>
#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/IMethod.h>
#include <jsonrpc/rpc/Registry.h>
#include <jsonrpc/rpc/Request.h>
#include <jsonrpc/rpc/Response.h>
#include <jsonrpc/util/Util.h>

#include <iostream>
#include <string>

namespace rpc
{

class Dispatcher : public net::IDispatcher
{
private:
	Registry _registry;

public:
	template <class METHOD>
	void add(const std::string& name)
	{
		_registry.emplace(name, std::make_unique<METHOD>());
	};

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
		auto method = _registry.find(req.method);
		if (method != _registry.end())
		{
			auto data = method->second->call(req.params);
			// TODO: if request without id, then request is a notification
			// TODO: the server must not reply to a notification
			return Response{"2.0", req.method, {}, req.id};
		}
		else
		{
			return Response{"2.0", {}, RPC_ERROR(ErrorCode::METHOD_NOT_FOUND, {}), req.id};
		}
	}
};

} // namespace rpc

#endif // HEADER_F4C30FD1_9561_11EA_A786_784F43782D09
