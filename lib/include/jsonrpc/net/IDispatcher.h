#ifndef HEADER_5E86F08A_9564_11EA_AFCA_784F43782D09
#define HEADER_5E86F08A_9564_11EA_AFCA_784F43782D09

#include <jsonrpc/Config.h>

#include <string>

namespace jsonrpc
{
namespace net
{

struct IDispatcher
{
	virtual std::string dispatch(const std::string& data) = 0;
	virtual ~IDispatcher()                                = default;
};

} // namespace net
} // namespace jsonrpc

#endif // HEADER_5E86F08A_9564_11EA_AFCA_784F43782D09
