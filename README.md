# JsonRPC

Modern C++ [JSON RPC](https://www.jsonrpc.org/specification) library

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
