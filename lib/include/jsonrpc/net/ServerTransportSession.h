#ifndef HEADER_F197C54C_9542_11EA_8827_784F43782D09
#define HEADER_F197C54C_9542_11EA_8827_784F43782D09

#include <jsonrpc/Config.h>
#include <jsonrpc/net/IDispatcher.h>

#include <boost/asio.hpp>

#include <string>

namespace jsonrpc
{
namespace net
{

class ServerTransportSession : public std::enable_shared_from_this<ServerTransportSession>
{
private:
	boost::asio::ip::tcp::socket _socket;
	std::string                  _rx;
	std::string                  _tx;
	net::IDispatcher&            _dispatcher;

public:
	ServerTransportSession(boost::asio::ip::tcp::socket socket, net::IDispatcher& dispatcher);

	void start();

private:
	void read();
	void write(const std::string& rpl);
};

} // namespace net
} // namespace jsonrpc

#endif // HEADER_F197C54C_9542_11EA_8827_784F43782D09
