#ifndef HEADER_CC88E9B5_9542_11EA_AB30_784F43782D09
#define HEADER_CC88E9B5_9542_11EA_AB30_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/net/IDispatcher.h>

#include <boost/asio.hpp>

namespace jsonrpc
{
namespace net
{

class ServerTransport
{
private:
	boost::asio::ip::tcp::acceptor _acceptor;
	net::IDispatcher&              _dispatcher;

public:
	ServerTransport(boost::asio::io_context& io_context, unsigned short port, net::IDispatcher& dispatcher);

private:
	void do_accept();
};

} // namespace net
} // namespace jsonrpc

#endif // HEADER_CC88E9B5_9542_11EA_AB30_784F43782D09
