#include <jsonrpc/Config.h>
#include <jsonrpc/net/Client.h>

using boost::asio::ip::tcp;

namespace net
{

Client::Client(boost::asio::io_context& ioc)
	: _ioc(ioc)
	, _socket(ioc)
{}

void Client::connect(const std::string& host, int port)
{
	tcp::resolver resolver(_ioc);
	boost::asio::connect(_socket, resolver.resolve(host.c_str(), std::to_string(port)));
}

std::string Client::send(const std::string& data)
{
	boost::asio::write(_socket, boost::asio::buffer(data));

	std::string reply;
	auto        n = boost::asio::read(_socket, boost::asio::dynamic_buffer(reply), boost::asio::transfer_at_least(1));
	return reply.substr(0, n);
}

} // namespace net