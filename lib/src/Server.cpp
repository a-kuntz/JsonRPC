#include <jsonrpc/Config.h>
#include <jsonrpc/net/Server.h>
#include <jsonrpc/net/TcpSession.h>

#include <memory>

using boost::asio::ip::tcp;

namespace net
{

Server::Server(boost::asio::io_context& io_context, unsigned short port)
	: _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
	do_accept();
}

void Server::do_accept()
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
