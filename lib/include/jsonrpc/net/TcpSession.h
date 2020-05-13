#ifndef HEADER_F197C54C_9542_11EA_8827_784F43782D09
#define HEADER_F197C54C_9542_11EA_8827_784F43782D09

#include <jsonrpc/Config.h>

#include <boost/asio.hpp>

#include <memory>
#include <string>

namespace net
{

using boost::asio::ip::tcp;

class TcpSession : public std::enable_shared_from_this<TcpSession>
{
private:
	tcp::socket _socket;
	std::string _data;

public:
	TcpSession(tcp::socket socket)
		: _socket(std::move(socket))
	{}

	void start()
	{
		do_read();
	}

private:
	void do_read()
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

	void do_write()
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
};

} // namespace net

#endif // HEADER_F197C54C_9542_11EA_8827_784F43782D09
