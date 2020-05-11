#ifndef HEADER_EC6C225C_9306_11EA_AB8A_784F43782D09
#define HEADER_EC6C225C_9306_11EA_AB8A_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Json.h>

#include <optional>
#include <string>

namespace rpc
{

struct Error
{
	int                 code;
	std::string         message;
	std::optional<Json> data;
};

void to_json(Json& json, const Error& err)
{
	if (err.data)
	{
		json = Json{{"code", err.code}, {"message", err.message}, {"data", err.data.value()}};
	}
	else
	{
		json = Json{{"code", err.code}, {"message", err.message}};
	}
}

void from_json(const Json& json, Error& err)
{
	json.at("code").get_to(err.code);
	json.at("message").get_to(err.message);

	auto data = json.find("data");
	err.data  = (data != json.end()) ? std::optional<Json>{*data} : std::optional<Json>{};
}

} // namespace rpc

#endif // HEADER_EC6C225C_9306_11EA_AB8A_784F43782D09
