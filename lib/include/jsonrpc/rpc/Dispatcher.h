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
		std::cout << util::ts() << " --> " << sreq << std::endl;
		std::string str_rsp;

		try
		{
			Request req = Json::parse(sreq);
			str_rsp     = Json(dispatch(req)).dump();

			// if request without id, then request is a notification
			// the server must not reply to a notification
			if (req.isNotification())
			{
				str_rsp = "";
			}
		}
		catch (const Json::parse_error& e)
		{
			str_rsp = Json(Response{"2.0", {}, RPC_ERROR(ErrorCode::PARSE_ERROR, {}), {}}).dump();
		}
		catch (const Json::type_error& e)
		{
			str_rsp = Json(Response{"2.0", {}, RPC_ERROR(ErrorCode::INVALID_REQUEST, {}), {}}).dump();
		}

		std::cout << util::ts() << " <-- " << str_rsp << std::endl;
		return str_rsp;
	};

private:
	Response dispatch(const Request& req)
	{
		auto method = _registry.find(req.method);
		if (method != _registry.end())
		{
			auto data = method->second->call(req.params);
			return Response{"2.0", data, {}, req.id};
		}
		else
		{
			return Response{"2.0", {}, RPC_ERROR(ErrorCode::METHOD_NOT_FOUND, {}), req.id};
		}
	}
};

} // namespace rpc

#endif // HEADER_F4C30FD1_9561_11EA_A786_784F43782D09
