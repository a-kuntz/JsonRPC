#ifndef HEADER_F4C30FD1_9561_11EA_A786_784F43782D09
#define HEADER_F4C30FD1_9561_11EA_A786_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/net/IDispatcher.h>
#include <jsonrpc/rpc/IMethod.h>
#include <jsonrpc/rpc/Registry.h>
#include <jsonrpc/rpc/Request.h>
#include <jsonrpc/rpc/Response.h>

#include <string>

namespace jsonrpc
{
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

	std::string dispatch(const std::string& sreq) override;

private:
	Response dispatch(const Request& req);
};

} // namespace rpc
} // namespace jsonrpc

#endif // HEADER_F4C30FD1_9561_11EA_A786_784F43782D09
