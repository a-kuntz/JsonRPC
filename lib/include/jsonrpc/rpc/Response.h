#ifndef HEADER_5718589E_92FC_11EA_9F6A_784F43782D09
#define HEADER_5718589E_92FC_11EA_9F6A_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Error.h>
#include <jsonrpc/rpc/Json.h>

#include <optional>
#include <string>

namespace rpc
{

struct Response
{
	std::string          jsonrpc;
	std::optional<Json>  result;
	std::optional<Error> error;
	id_t                 id;
};

inline void to_json(Json& j, const Response& rsp)
{
	if (rsp.result && !rsp.error)
	{
		j = Json{{"jsonrpc", rsp.jsonrpc}, {"result", rsp.result.value()}, {"id", rsp.id}};
	}
	else if (!rsp.result && rsp.error)
	{
		j = Json{{"jsonrpc", rsp.jsonrpc}, {"error", rsp.error.value()}, {"id", rsp.id}};
	}
	else
	{
		throw std::logic_error("invalid response: expected exactly one of {result, error}.");
	}
}

inline void from_json(const Json& json, Response& rsp)
{
	auto result = json.find("result");
	auto error  = json.find("error");

	if (result != json.end() && error == json.end())
	{
		rsp.result = json.at("result");
		rsp.error  = {};
	}
	else if (result == json.end() && error != json.end())
	{
		rsp.result = {};
		rsp.error  = json.at("error");
	}
	else
	{
		throw std::logic_error("invalid response: expected exactly one of {result, error}.");
	}

	json.at("jsonrpc").get_to(rsp.jsonrpc);
	json.at("id").get_to(rsp.id);
}

} // namespace rpc

#endif // HEADER_5718589E_92FC_11EA_9F6A_784F43782D09
