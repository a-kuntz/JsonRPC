#ifndef HEADER_4261025E_9499_11EA_AA8C_784F43782D09
#define HEADER_4261025E_9499_11EA_AA8C_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/net/ITransport.h>

#include <boost/asio.hpp>
#include <string>

namespace net
{

class ClientTransport : public ITransport
{
private:
	boost::asio::io_context&     _ioc;
	boost::asio::ip::tcp::socket _socket;

public:
	ClientTransport(boost::asio::io_context& ioc);

	void connect(const std::string& host, int port);

	std::string send(const std::string& data) override;
};

} // namespace net

#endif // HEADER_4261025E_9499_11EA_AA8C_784F43782D09
