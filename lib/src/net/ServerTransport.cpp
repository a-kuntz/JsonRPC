#include <jsonrpc/Config.h>
#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/net/ServerSession.h>

#include <memory>

using boost::asio::ip::tcp;

namespace jsonrpc
{
namespace net
{

ServerTransport::ServerTransport(boost::asio::io_context& io_context, unsigned short port, net::IDispatcher& dispatcher)
	: _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
	, _dispatcher(dispatcher)
{
	do_accept();
}

void ServerTransport::do_accept()
{
	_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
		if (!ec)
		{
			std::make_shared<ServerSession>(std::move(socket), _dispatcher)->start();
		}

		do_accept();
	});
}

} // namespace net
} // namespace jsonrpc
