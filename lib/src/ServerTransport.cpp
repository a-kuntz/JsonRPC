#include <jsonrpc/Config.h>
#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/net/TcpSession.h>

#include <memory>

using boost::asio::ip::tcp;

namespace net
{

ServerTransport::ServerTransport(boost::asio::io_context& io_context, unsigned short port)
	: _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
	do_accept();
}

void ServerTransport::do_accept()
{
	_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
		if (!ec)
		{
			std::make_shared<TcpSession>(std::move(socket))->start();
		}

		do_accept();
	});
}

} // namespace net
