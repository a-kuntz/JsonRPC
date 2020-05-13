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
	Json        params;
	id_t        id;
};

void to_json(Json& json, const Request& req)
{
	json = Json{{"jsonrpc", req.jsonrpc}, {"method", req.method}, {"params", req.params}, {"id", req.id}};
}

void from_json(const Json& json, Request& req)
{
	json.at("jsonrpc").get_to(req.jsonrpc);
	json.at("method").get_to(req.method);
	req.params = json.at("params");
	json.at("id").get_to(req.id);
}

} // namespace rpc

#endif // HEADER_2F59322E_92F7_11EA_9544_784F43782D09
