# JsonRPC

Modern C++ [JSON RPC 2.0](https://www.jsonrpc.org/specification) library

## Use the library

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

### More examples

You can find additional usage examples in the test folder, in particular see [client server test](test/src/ClientServerTest.cpp).


## Building the library

### Install development tools

On an Ubuntu 20.04, to setup your machine for building the library, execute the following command:

```shell
wget -qO - https://raw.githubusercontent.com/a-kuntz/JsonRPC/master/scripts/bootstrap-ubuntu-20-04.sh | sh
```

### Clone the repo

```shell
git clone https://github.com/a-kuntz/JsonRPC.git
cd JsonRPC
```


### Build

To build the library, type:

```shell
conan install . --install-folder=build -pr:b=default -s build_type=Debug
cmake -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON -DBUILD_EXAMPLE=ON
cmake --build build
```

### Dependencies

JsonRPC directly depends on the following libraries, which are handled through conan (see [conanfile.txt](conanfile.txt) for details):

- [boost](https://www.boost.org) version 1.75.0
- [fmt](https://github.com/fmtlib/fmt) version 7.1.3
- [nlohmann_json](https://github.com/nlohmann/json) vesion 3.9.1
- [gtest](https://github.com/google/googletest) version 1.11.0 (for testing purposes only)

| tool      | requirement    |
| --------- | -------------- |
| g++/clang | c++17          |
| cmake     | version 3.16   |
| conan     | version 1.53   |
