#ifndef HEADER_4261025E_9499_11EA_AA8C_784F43782D09
#define HEADER_4261025E_9499_11EA_AA8C_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/net/ITransport.h>

#include <boost/asio.hpp>
#include <string>

namespace net
{
// TODO: move using to cpp
using boost::asio::ip::tcp;

class Client : public ITransport
{
private:
	boost::asio::io_context& _ioc;
	tcp::socket              _socket;

public:
	Client(boost::asio::io_context& ioc)
		: _ioc(ioc)
		, _socket(ioc)
	{}

	// ~Client() override {}

	void connect(const std::string& host, int port)
	{
		tcp::resolver resolver(_ioc);
		boost::asio::connect(_socket, resolver.resolve(host.c_str(), std::to_string(port)));
	}

	std::string send(const std::string& data) override
	{
		boost::asio::write(_socket, boost::asio::buffer(data));

		std::string               reply;
		boost::system::error_code ec;
		auto n = boost::asio::read(_socket, boost::asio::dynamic_buffer(reply), boost::asio::transfer_at_least(1), ec);
		return reply.substr(0, n);
	}
};

} // namespace net

#endif // HEADER_4261025E_9499_11EA_AA8C_784F43782D09
