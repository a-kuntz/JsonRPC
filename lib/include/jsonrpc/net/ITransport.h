#ifndef HEADER_6D442305_9481_11EA_80C5_784F43782D09
#define HEADER_6D442305_9481_11EA_80C5_784F43782D09

#include <jsonrpc/Config.h>

#include <string>

namespace net
{

struct ITransport
{
	virtual std::string send(const std::string& data) = 0;
	virtual ~ITransport()                             = default;
};

} // namespace net

#endif // HEADER_6D442305_9481_11EA_80C5_784F43782D09
