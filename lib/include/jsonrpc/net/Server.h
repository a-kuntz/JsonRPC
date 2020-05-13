#ifndef HEADER_CC88E9B5_9542_11EA_AB30_784F43782D09
#define HEADER_CC88E9B5_9542_11EA_AB30_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/net/TcpSession.h>

#include <boost/asio.hpp>

namespace net
{

using boost::asio::ip::tcp;

class Server
{
private:
	tcp::acceptor _acceptor;

public:
	Server(boost::asio::io_context& io_context, unsigned short port)
		: _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
	{
		do_accept();
	}

private:
	void do_accept()
	{
		_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
			if (!ec)
			{
				std::make_shared<TcpSession>(std::move(socket))->start();
			}

			do_accept();
		});
	}
};

} // namespace net

#endif // HEADER_CC88E9B5_9542_11EA_AB30_784F43782D09
