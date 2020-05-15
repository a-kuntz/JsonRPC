#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <gtest/gtest.h>

#include <array>
#include <string>

namespace
{
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

} // namespace

TEST(DispatcherTest, FooBar)
{
	rpc::Dispatcher dsp;
	dsp.add<Foo>("foo");
	dsp.add<Bar>("bar");

	ASSERT_EQ(
		dsp.dispatch(R"({"id":"1","jsonrpc":"2.0","method":"foo","params":["arg1","arg2","arg3"]})"),
		R"({"id":"1","jsonrpc":"2.0","result":"foo called"})");

	ASSERT_EQ(
		dsp.dispatch(R"({"id":"2","jsonrpc":"2.0","method":"bar","params":"params"})"),
		R"({"id":"2","jsonrpc":"2.0","result":"bar called"})");

	ASSERT_EQ(
		dsp.dispatch(R"({"id":"3","jsonrpc":"2.0","method":"unknown method","params":null})"),
		R"({"error":{"code":-32601,"message":"Method not found"},"id":"3","jsonrpc":"2.0"})");
}

namespace
{

struct Substract : public rpc::IMethod
{
	rpc::Json call(const rpc::Json& params) override
	{
		std::array<int, 2> par = params;
		return par[0] - par[1];
	}
};

} // namespace

TEST(DispatcherTest, SpecificationExamples)
{
	rpc::Dispatcher dsp;
	dsp.add<Substract>("subtract");

	auto rx = [&](const std::string& s) { return rpc::Json::parse(dsp.dispatch(s)); };
	auto tx = [&](const std::string& s) { return rpc::Json::parse(s); };

	// --> {"jsonrpc": "2.0", "method": "subtract", "params": [42, 23], "id": 1}
	// <-- {"jsonrpc": "2.0", "result": 19, "id": 1}
	ASSERT_EQ(
		rx(R"({"jsonrpc": "2.0", "method": "subtract", "params": [42, 23], "id": 1})"),
		tx(R"({"jsonrpc": "2.0", "result": 19, "id": 1})"));

	// --> {"jsonrpc": "2.0", "method": "subtract", "params": [23, 42], "id": 2}
	// <-- {"jsonrpc": "2.0", "result": -19, "id": 2}
	ASSERT_EQ(
		rx(R"({"jsonrpc": "2.0", "method": "subtract", "params": [23, 42], "id": 2})"),
		tx(R"({"jsonrpc": "2.0", "result": -19, "id": 2})"));
}
