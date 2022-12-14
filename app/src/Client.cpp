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
		if (argc != 4 && argc != 5)
		{
			std::cerr << "Usage: " << argv[0] << " <host> <port> <command> [<arg>]\n";
			return 1;
		}

		boost::asio::io_context io_context;

		net::ClientTransport transport(io_context);
		transport.connect(argv[1], atoi(argv[2]));

		auto client = rpc::Client(transport);

		auto result = client.call(argv[3], (argc == 5 ? rpc::Json::parse(argv[4]) : rpc::Json{}));

		std::cout << result << "\n";
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
