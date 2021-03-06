#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Response.h>

#include <gtest/gtest.h>

#include <string>

using namespace jsonrpc;

TEST(ResponseTest, SerializeResult)
{
	rpc::Response rsp  = {"2.0", "result-value", {}, "1"};
	rpc::Json     json = rsp;
	auto          rsp2 = json.get<rpc::Response>();

	ASSERT_EQ(R"({"id":"1","jsonrpc":"2.0","result":"result-value"})", json.dump());
	ASSERT_EQ(rsp.jsonrpc, rsp2.jsonrpc);
	ASSERT_EQ(rsp.result, rsp2.result);
	ASSERT_EQ(!!rsp.error, !!rsp2.error);
	ASSERT_EQ(rsp.id, rsp2.id);
}

TEST(ResponseTest, SerializeError)
{
	rpc::Response rsp  = {"2.0", {}, rpc::Error{rpc::ErrorCode::INTERNAL_ERROR, "some-error", {}}, "1"};
	rpc::Json     json = rsp;
	auto          rsp2 = json.get<rpc::Response>();

	ASSERT_EQ(R"({"error":{"code":-32603,"message":"some-error"},"id":"1","jsonrpc":"2.0"})", json.dump());
	ASSERT_EQ(rsp.jsonrpc, rsp2.jsonrpc);
	ASSERT_EQ(!!rsp.result, !!rsp2.result);
	ASSERT_EQ(rsp.error->code, rsp2.error->code);
	ASSERT_EQ(rsp.error->message, rsp2.error->message);
	ASSERT_EQ(rsp.error->data, rsp2.error->data);
	ASSERT_EQ(rsp.id, rsp2.id);
}
