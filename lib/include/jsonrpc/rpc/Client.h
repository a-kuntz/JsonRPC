#ifndef HEADER_BA6F4438_955A_11EA_9437_784F43782D09
#define HEADER_BA6F4438_955A_11EA_9437_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/net/ITransport.h>
#include <jsonrpc/rpc/Json.h>
#include <jsonrpc/rpc/Request.h>
#include <jsonrpc/rpc/Response.h>

namespace jsonrpc
{
namespace rpc
{

class Client
{
private:
	net::ITransport& _transport;
	int              _id = 0;

public:
	Client(net::ITransport& transport);

	Json call(const std::string name, const Json& args);

	void notify(const std::string name, const Json& args);

private:
	Response call(const Request& req);
};

} // namespace rpc
} // namespace jsonrpc

#endif // HEADER_BA6F4438_955A_11EA_9437_784F43782D09
