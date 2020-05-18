#ifndef HEADER_EC6C225C_9306_11EA_AB8A_784F43782D09
#define HEADER_EC6C225C_9306_11EA_AB8A_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Json.h>

#include <optional>
#include <string>

namespace jsonrpc
{
namespace rpc
{

enum class ErrorCode : int
{
	PARSE_ERROR = -32700,      // Parse error	Invalid JSON was received by the server.
							   // An error occurred on the server while parsing the JSON text.
	INVALID_REQUEST  = -32600, // Invalid Request	The JSON sent is not a valid Request object.
	METHOD_NOT_FOUND = -32601, // Method not found	The method does not exist / is not available.
	INVALID_PARAMS   = -32602, // Invalid params	Invalid method parameter(s).
	INTERNAL_ERROR   = -32603, // Internal error	Internal JSON-RPC error.
							   // -32000 to -32099	Server error	Reserved for implementation-defined server-errors.
};

template <const ErrorCode>
std::string to_string();

template <>
inline std::string to_string<ErrorCode::PARSE_ERROR>()
{
	return "Parse error";
}

template <>
inline std::string to_string<ErrorCode::INVALID_REQUEST>()
{
	return "Invalid Request";
}

template <>
inline std::string to_string<ErrorCode::METHOD_NOT_FOUND>()
{
	return "Method not found";
}

template <>
inline std::string to_string<ErrorCode::INVALID_PARAMS>()
{
	return "Invalid params";
}

template <>
inline std::string to_string<ErrorCode::INTERNAL_ERROR>()
{
	return "Internal error";
}

struct Error
{
	ErrorCode           code;
	std::string         message;
	std::optional<Json> data;
};

#define RPC_ERROR(code, data)              \
	rpc::Error                             \
	{                                      \
		code, rpc::to_string<code>(), data \
	}

inline void to_json(Json& json, const Error& err)
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

inline void from_json(const Json& json, Error& err)
{
	json.at("code").get_to(err.code);
	json.at("message").get_to(err.message);

	auto data = json.find("data");
	err.data  = (data != json.end()) ? std::optional<Json>{*data} : std::optional<Json>{};
}

} // namespace rpc
} // namespace jsonrpc

#endif // HEADER_EC6C225C_9306_11EA_AB8A_784F43782D09
