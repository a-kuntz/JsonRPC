#ifndef HEADER_364CC7AB_961A_11EA_83FD_784F43782D09
#define HEADER_364CC7AB_961A_11EA_83FD_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/IMethod.h>

#include <map>
#include <memory>

namespace rpc
{

using Registry = std::map<const std::string, std::unique_ptr<rpc::IMethod>>;

} // namespace rpc

#endif // HEADER_364CC7AB_961A_11EA_83FD_784F43782D09
