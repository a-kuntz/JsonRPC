#include <jsonrpc/Config.h>
#include <jsonrpc/net/TcpSession.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>

using boost::asio::ip::tcp;

namespace net
{

namespace
{
auto ts()
{
	auto pt = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(pt);
	return std::put_time(std::localtime(&tt), "%F %T");
}
} // namespace

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
				std::cout << ts() << " > " << _data << std::endl;
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
				std::cout << ts() << " < " << _data << std::endl;
				do_read();
			}
		});
}

} // namespace net
