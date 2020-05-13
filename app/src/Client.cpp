#include <jsonrpc/Config.h>
#include <jsonrpc/net/ClientTransport.h>
#include <jsonrpc/rpc/Client.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

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

		// std::cout << "Enter message: ";
		// std::string request;
		// std::getline(std::cin, request);

		// std::cout << "< " << request << std::endl;
		// std::cout << "> " << transport.send(request) << std::endl;

		auto client = rpc::Client(transport);
		client.call("foo", rpc::Json{"args"});
		client.call("bar", rpc::Json{"params"});
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
