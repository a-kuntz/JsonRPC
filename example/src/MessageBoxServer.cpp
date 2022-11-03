#include <jsonrpc/net/ServerTransport.h>
#include <jsonrpc/rpc/Dispatcher.h>
#include <jsonrpc/util/Util.h>

#include <boost/asio.hpp>
#include <fmt/core.h>

#include <cstdlib>
#include <exception>
#include <iostream>

using namespace jsonrpc;

struct Msg
{
	std::string from;
	std::string msg;
	std::string ts;
};
using MBox = std::map<std::string, std::vector<Msg>>;
// using MBox = std::map<std::string, std::vector<std::pair<std::string, std::string>>>;

struct Add : public rpc::IMethod
{
	Add(MBox& mbox)
		: _mbox(mbox)
	{}
	rpc::Json call(const rpc::Json& data) override
	{
		// args: name
		// add if name is new
		const std::string name = data;

		if (_mbox.count(name))
		{
			return fmt::format("name '{}' already exists", name);
		}

		_mbox[name] = {};

		return fmt::format("name '{}' added", name);
	}

private:
	MBox& _mbox;
};

struct List : public rpc::IMethod
{
	List(MBox& mbox)
		: _mbox(mbox)
	{}
	rpc::Json call(const rpc::Json& data) override
	{
		// list added names
		rpc::Json result = nlohmann::json::array();

		for (const auto& item : _mbox)
		{
			result += item.first;
		}
		return result;
	}

private:
	MBox& _mbox;
};

struct Send : public rpc::IMethod
{
	Send(MBox& mbox)
		: _mbox(mbox)
	{}
	rpc::Json call(const rpc::Json& data) override
	{
		// args: from, to, message
		// store message for name

		const std::string from = data["from"];
		const std::string to   = data["to"];
		const std::string msg  = data["msg"];

		if (!_mbox.count(from))
		{
			return fmt::format("unknown from name '{}'", to);
		}

		if (!_mbox.count(to))
		{
			return fmt::format("unknown to name '{}'", to);
		}

		std::stringstream ss;
		ss << util::ts();

		_mbox.at(to).push_back(Msg{from, msg, ss.str()});

		return fmt::format("{} messages for {}", _mbox.at(to).size(), to);
	}

private:
	MBox& _mbox;
};

struct Receive : public rpc::IMethod
{
	Receive(MBox& mbox)
		: _mbox(mbox)
	{}
	rpc::Json call(const rpc::Json& data) override
	{
		// args: name
		// return and delete messages for name

		const std::string name = data;

		if (!_mbox.count(name))
		{
			return fmt::format("unknown name '{}'", name);
		}

		rpc::Json result = nlohmann::json::array();

		for (const auto& msg : _mbox.at(name))
		{
			result += rpc::Json{{"from", msg.from}, {"ts", msg.ts}, {"msg", msg.msg}};
		}
		_mbox.at(name).clear();

		return result;
	}

private:
	MBox& _mbox;
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

		MBox mbox;

		rpc::Dispatcher dsp;
		dsp.add<Add>("add", mbox);
		dsp.add<List>("list", mbox);
		dsp.add<Send>("send", mbox);
		dsp.add<Receive>("receive", mbox);
		net::ServerTransport st(io_context, std::atoi(argv[1]), dsp);

		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
