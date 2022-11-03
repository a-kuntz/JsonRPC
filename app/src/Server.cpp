// #include "XRayTube.h"

#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <boost/asio.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>

using namespace jsonrpc;

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: " << argv[0] << " <port>\n";
			return 1;
		}

		boost::asio::io_context io_context;

		xray::Server server(io_context, std::atoi(argv[1]));

		std::cerr << argv[0] << " listening on port " << argv[1] << "\n";

		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
