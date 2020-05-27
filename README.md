# JsonRPC

Modern C++ [JSON RPC 2.0](https://www.jsonrpc.org/specification) library

## Usage

### Server

```c++
struct Foo : public rpc::IMethod
{
    rpc::Json call(const rpc::Json& data) override
    {
        // your custom foo implementation
        return "foo called";
    }
};

int main(int argc, char* argv[])
{
    boost::asio::io_context io_context;

    rpc::Dispatcher dispatcher;
    dispatcher.add<Foo>("foo");
    net::ServerTransport st(io_context, 5555, dispatcher);

    io_context.run();
}
```

See [server example](example/src/Server.cpp)

### Client

```c++
int main(int argc, char* argv[])
{
    boost::asio::io_context io_context;

    net::ClientTransport transport(io_context);
    transport.connect("localhost", 5555);

    auto client = rpc::Client(transport);
    client.call("foo", {"arg1", "arg2", "arg3"});
}
```

See [client example](example/src/Client.cpp)

### Examples

You can find plenty of usage examples in the test folder, in particular see [client server test](test/src/ClientServerTest.cpp).

## Build

See [`scripts/build.sh`](scripts/build.sh) or do

```shell
mkdir build; cd build
conan install ..
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake
make all test
```

### Dependencies

The following dependencies are handled by `conan`, see [`conanfile.txt`](conanfile.txt):

- [gtest](https://github.com/google/googletest) version 1.10.0
- [nlohmann_json](https://github.com/nlohmann/json) vesion 3.7.3
- [boost](https://www.boost.org) version 1.73.0
<!-- - [fmt](https://github.com/fmtlib/fmt) version 6.2.0 -->

``` shell
cd build
conan install ..
```

### Toolchain

| tool      | requirement    |
| --------- | -------------- |
| g++/clang | c++17          |
| cmake     | version 3.12   |
| conan     | version 1.25.1 |
