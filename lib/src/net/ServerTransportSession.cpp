#include <jsonrpc/Config.h>
#include <jsonrpc/net/ServerTransportSession.h>
#include <jsonrpc/util/Util.h>

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

	auto buffer = std::make_unique<std::string>();

	boost::asio::async_read(
		_socket, boost::asio::dynamic_string_buffer(*buffer), boost::asio::transfer_at_least(1),
		[this, self, buffer = std::move(buffer)](boost::system::error_code ec, std::size_t /*length*/) {
			if (!ec)
			{
				util::for_each_split(*buffer, "}{", [this](const std::string& token) {
					std::cout << token << std::endl;
					write(_dispatcher.dispatch(token));
				});
			}
		});
}

void ServerTransportSession::write(const std::string& rpl)
{
	auto self(shared_from_this());

	if (rpl.length())
	{
		boost::asio::async_write(
			_socket, boost::asio::const_buffer(rpl.data(), rpl.size()),
			[this, self](boost::system::error_code ec, std::size_t /*length*/) {
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
