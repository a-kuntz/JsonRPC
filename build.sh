#!/bin/bash

set -euo pipefail

BUILD=build

mkdir -p ${BUILD}
pushd ${BUILD}
	conan install .. --install-folder=build -pr:b=default -s build_type=Debug
	cmake ..
	cmake -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug .
	ctest --verbose
popd
