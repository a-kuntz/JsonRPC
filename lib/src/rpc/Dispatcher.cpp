#include <jsonrpc/Config.h>
#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>
#include <jsonrpc/util/Util.h>

#include <iostream>

namespace jsonrpc
{
namespace rpc
{

std::string Dispatcher::dispatch(const std::string& sreq)
{
	std::cout << util::ts() << " --> " << sreq << std::endl;
	Json jrsp;

	try
	{
		const auto jreq = Json::parse(sreq);
		jrsp            = (jreq.is_array() && !jreq.empty()) ? batch(jreq) : dispatch(jreq);
	}
	catch (const Json::parse_error& e)
	{
		jrsp = Json(Response{"2.0", {}, RPC_ERROR(ErrorCode::PARSE_ERROR, {}), {}});
	}

	const auto str_rsp = jrsp.is_null() || (jrsp.is_array() && jrsp.empty()) ? "" : jrsp.dump();
	std::cout << util::ts() << " <-- " << str_rsp << std::endl;
	return str_rsp;
};

Json Dispatcher::batch(const Json& jreq)
{
	Json jrsp = Json::array();
	for (const auto& req : jreq)
	{
		const auto rsp = dispatch(req);
		if (!rsp.is_null())
		{
			jrsp.push_back(rsp);
		}
	}

	return jrsp;
}

Json Dispatcher::dispatch(const Json& jreq)
{
	Json jrsp;
	try
	{
		Request req = jreq;
		jrsp        = Json(dispatch(req));

		// if request without id, then request is a notification
		// the server must not reply to a notification
		if (req.isNotification())
		{
			jrsp = Json();
		}
	}
	catch (const Json::type_error& e)
	{
		jrsp = Json(Response{"2.0", {}, RPC_ERROR(ErrorCode::INVALID_REQUEST, {}), {}});
	}
	return jrsp;
}

Response Dispatcher::dispatch(const Request& req)
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
};

} // namespace rpc
} // namespace jsonrpc