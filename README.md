# JsonRPC

Modern C++ [JSON RPC](https://www.jsonrpc.org/specification) library

## usage

### server

```c++
struct Foo : public rpc::IMethod
{
    rpc::Json call(const rpc::Json& data) override
    {
      return "foo called";
    }
};

int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_context io_context;

        rpc::Dispatcher dispatcher;
        dispatcher.add<Foo>("foo");
        net::ServerTransport st(io_context, 5555, dispatcher);

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
```

see [server example](example/src/Server.cpp)

### client

```c++
int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_context io_context;

        net::ClientTransport transport(io_context);
        transport.connect("localhost", 5555);

        auto client = rpc::Client(transport);
        client.call("foo", {"arg1", "arg2", "arg3"});
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
```

see [client example](example/src/Client.cpp)

## build

see [`scripts/build.sh`](scripts/build.sh) or do

```shell
mkdir build; cd build
conan install ..
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake
make all test
```

### dependencies

The following dependencies are handled by `conan`, see [`conanfile.txt`](conanfile.txt):

- [gtest](https://github.com/google/googletest) version 1.10.0
- [nlohmann_json](https://github.com/nlohmann/json) vesion 3.7.3
- [boost](https://www.boost.org) version 1.73.0
<!-- - [fmt](https://github.com/fmtlib/fmt) version 6.2.0 -->

``` shell
cd build
conan install ..
```

### toolchain

| tool      | requirement    |
| --------- | -------------- |
| g++/clang | c++17          |
| cmake     | version 3.12   |
| conan     | version 1.25.1 |
