#ifndef HEADER_2F59322E_92F7_11EA_9544_784F43782D09
#define HEADER_2F59322E_92F7_11EA_9544_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Json.h>

#include <string>

namespace rpc
{

struct Request
{
	std::string jsonrpc;
	std::string method;
	Json        params; // TODO: param is optional
	Json        id;     // TODO: support allowe id types: string, number or null type
						// TODO: support notification as Request without id

	bool isNotification() const
	{
		return id.is_null();
	}
};

inline void to_json(Json& json, const Request& req)
{
	json = Json{{"jsonrpc", req.jsonrpc}, {"method", req.method}, {"params", req.params}, {"id", req.id}};
}

inline void from_json(const Json& json, Request& req)
{
	json.at("jsonrpc").get_to(req.jsonrpc);
	json.at("method").get_to(req.method);
	req.params = (json.find("params") != json.end()) ? json.at("params") : Json{};
	req.id     = (json.find("id") != json.end()) ? json.at("id") : Json{};
}

} // namespace rpc

#endif // HEADER_2F59322E_92F7_11EA_9544_784F43782D09
