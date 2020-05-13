#ifndef HEADER_CC88E9B5_9542_11EA_AB30_784F43782D09
#define HEADER_CC88E9B5_9542_11EA_AB30_784F43782D09

#include <jsonrpc/Config.h>

#include <boost/asio.hpp>

namespace net
{

class ServerTransport
{
private:
	boost::asio::ip::tcp::acceptor _acceptor;

public:
	ServerTransport(boost::asio::io_context& io_context, unsigned short port);

private:
	void do_accept();
};

} // namespace net

#endif // HEADER_CC88E9B5_9542_11EA_AB30_784F43782D09
