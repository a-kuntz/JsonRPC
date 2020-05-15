#include <jsonrpc/Config.h>
#include <jsonrpc/rpc/Request.h>

#include <gtest/gtest.h>

#include <string>

TEST(RequestTest, serialization)
{
	rpc::Request req  = {"2.0", "substract", {}, "1"};
	rpc::Json    json = req;
	auto         req2 = json.get<rpc::Request>();

	ASSERT_EQ(req.jsonrpc, req2.jsonrpc);
	ASSERT_EQ(req.method, req2.method);
	ASSERT_EQ(req.params, req2.params);
	ASSERT_EQ(req.id, req2.id);
}
