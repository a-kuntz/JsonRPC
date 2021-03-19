#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <boost/asio.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>

using namespace jsonrpc;

struct Foo : public rpc::IMethod
{
	rpc::Json call(const rpc::Json& data) override
	{
		return "foo called";
	}
};

struct Bar : public rpc::IMethod
{
	rpc::Json call(const rpc::Json& data) override
	{
		return "bar called";
	}
};

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

		rpc::Dispatcher dsp;
		dsp.add<Foo>("foo");
		dsp.add<Bar>("bar");
		net::ServerTransport st(io_context, std::atoi(argv[1]), dsp);

		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
