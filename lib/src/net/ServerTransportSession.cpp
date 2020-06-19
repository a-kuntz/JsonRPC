#include <jsonrpc/Config.h>
#include <jsonrpc/net/ServerTransportSession.h>

#include <iostream>
#include <memory>

using boost::asio::ip::tcp;

namespace jsonrpc
{
namespace net
{

ServerTransportSession::ServerTransportSession(tcp::socket socket, net::IDispatcher& dispatcher)
	: _socket(std::move(socket))
	, _dispatcher(dispatcher)
{}

void ServerTransportSession::start()
{
	read();
}

void ServerTransportSession::read()
{
	auto self(shared_from_this());

	_rx = "";

	boost::asio::async_read(
		_socket, boost::asio::dynamic_buffer(_rx), boost::asio::transfer_at_least(1),
		[this, self](boost::system::error_code ec, std::size_t /*length*/) {
			if (!ec)
			{
				// std::string s         = _rx;
				// std::string delimiter = "}{";

				// size_t      pos = 0;
				// std::string token;
				// while ((pos = s.find(delimiter)) != std::string::npos)
				// {
				// 	token = s.substr(0, pos+1);
				// 	std::cout << token << std::endl;
				// 	s.erase(0, pos + delimiter.length()-1);
				// }
				// std::cout << s << std::endl;

				write(_dispatcher.dispatch(_rx));
			}
		});
}

void ServerTransportSession::write(const std::string& rpl)
{
	auto self(shared_from_this());

	_tx = rpl;

	if (_tx.length())
	{
		boost::asio::async_write(
			_socket, boost::asio::buffer(_tx), [this, self](boost::system::error_code ec, std::size_t /*length*/) {
				if (!ec)
				{
					read();
				}
			});
	}
	else
	{
		read();
	}
}

} // namespace net
} // namespace jsonrpc
