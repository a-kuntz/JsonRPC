#include <jsonrpc/Config.h>
#include <jsonrpc/net/ClientTransport.h>
#include <jsonrpc/rpc/Client.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;
using namespace jsonrpc;

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: " << argv[0] << " <host> <port>\n";
			return 1;
		}

		boost::asio::io_context io_context;

		net::ClientTransport transport(io_context);
		transport.connect(argv[1], atoi(argv[2]));

		auto client = rpc::Client(transport);
		client.call("add", "john");
		client.call("add", "fred");
		client.call("list", {});
		client.call("send", {{"to", "fred"}, {"from", "john"}, {"msg", "hi fred"}});
		client.call("receive", "fred");
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
