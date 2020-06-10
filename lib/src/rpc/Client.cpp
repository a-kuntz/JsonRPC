#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Client.h>
#include <jsonrpc/util/Util.h>

#include <iostream>

namespace jsonrpc
{
namespace rpc
{

Client::Client(net::ITransport& transport)
	: _transport(transport)
{}

Json Client::call(const std::string name, const Json& args)
{
	auto rsp = call(Request{"2.0", name, args, std::to_string(++_id)});

	if (rsp.result)
	{
		return *rsp.result;
	}
	else if (rsp.error)
	{
		return *rsp.error;
	}

	throw std::logic_error("response without result and error");
}

void Client::notify(const std::string name, const Json& args)
{
	call(Request{"2.0", name, args, {}});
}

Response Client::call(const Request& req)
{
	Json jreq = req;
	auto sreq = jreq.dump();

	std::cout << util::ts() << " <<< " << sreq << std::endl;
	_transport.send(sreq);

	if (req.isNotification())
	{
		return {};
	}

	auto srsp = _transport.receive();
	std::cout << util::ts() << " >>> " << srsp << std::endl;
	auto jrsp = Json::parse(srsp);
	return jrsp;
}

} // namespace rpc
} // namespace jsonrpc
