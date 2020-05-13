#include <jsonrpc/Config.h>
#include <jsonrpc/net/TcpSession.h>

#include <memory>

using boost::asio::ip::tcp;

namespace net
{

TcpSession::TcpSession(tcp::socket socket)
	: _socket(std::move(socket))
{}

void TcpSession::start()
{
	do_read();
}

void TcpSession::do_read()
{
	auto self(shared_from_this());
	boost::asio::async_read(
		_socket, boost::asio::dynamic_buffer(_data), boost::asio::transfer_at_least(1),
		[this, self](boost::system::error_code ec, std::size_t /*length*/) {
			if (!ec)
			{
				do_write();
			}
		});
}

void TcpSession::do_write()
{
	auto self(shared_from_this());
	boost::asio::async_write(
		_socket, boost::asio::buffer(_data), [this, self](boost::system::error_code ec, std::size_t /*length*/) {
			if (!ec)
			{
				do_read();
			}
		});
}

} // namespace net