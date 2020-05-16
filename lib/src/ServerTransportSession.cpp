#include <jsonrpc/Config.h>
#include <jsonrpc/net/ServerTransportSession.h>

#include <memory>

using boost::asio::ip::tcp;

namespace net
{

ServerTransportSession::ServerTransportSession(tcp::socket socket, net::IDispatcher& dispatcher)
	: _socket(std::move(socket))
	, _dispatcher(dispatcher)
{}

void ServerTransportSession::start()
{
	do_read();
}

void ServerTransportSession::do_read()
{
	auto self(shared_from_this());

	_data = "";

	boost::asio::async_read(
		_socket, boost::asio::dynamic_buffer(_data), boost::asio::transfer_at_least(1),
		[this, self](boost::system::error_code ec, std::size_t /*length*/) {
			if (!ec)
			{
				do_write();
			}
		});
}

void ServerTransportSession::do_write()
{
	auto self(shared_from_this());

	_data = _dispatcher.dispatch(_data);

	boost::asio::async_write(
		_socket, boost::asio::buffer(_data), [this, self](boost::system::error_code ec, std::size_t /*length*/) {
			if (!ec)
			{
				do_read();
			}
		});
}

} // namespace net
