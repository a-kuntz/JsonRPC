#ifndef HEADER_0A456FA8_9619_11EA_9CBF_784F43782D09
#define HEADER_0A456FA8_9619_11EA_9CBF_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Json.h>

#include <string>

namespace jsonrpc
{
namespace rpc
{

struct IMethod
{
	virtual ~IMethod()                  = default;
	virtual Json call(const Json& args) = 0;
};

} // namespace rpc
} // namespace jsonrpc

#endif // HEADER_0A456FA8_9619_11EA_9CBF_784F43782D09
