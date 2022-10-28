#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>
#include "workshop/x_ray_tube/x_ray_tube.h"

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
			std::cerr << "Usage: async_tcp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_context io_context;

		rpc::Dispatcher dsp;
		dsp.add<XRayTube::setTubeVoltage>("setTubeVoltage");
		dsp.add<XRayTube::setTubeCurrent>("setTubeCurrent");
		dsp.add<XRayTube::getStatus>("getStatus");
		dsp.add<XRayTube::takePicture>("takePicture");

		net::ServerTransport st(io_context, std::atoi(argv[1]), dsp);

		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
