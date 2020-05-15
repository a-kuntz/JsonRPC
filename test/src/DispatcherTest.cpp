#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Dispatcher.h>

#include <gtest/gtest.h>

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
		R"({"id":"1","jsonrpc":"2.0","result":"foo"})");

	ASSERT_EQ(
		dsp.dispatch(R"({"id":"2","jsonrpc":"2.0","method":"bar","params":"params"})"),
		R"({"id":"2","jsonrpc":"2.0","result":"bar"})");

	ASSERT_EQ(
		dsp.dispatch(R"({"id":"3","jsonrpc":"2.0","method":"unknown method","params":null})"),
		R"({"error":{"code":-32601,"message":"Method not found"},"id":"3","jsonrpc":"2.0"})");
}
