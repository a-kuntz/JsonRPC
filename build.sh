#!/bin/bash

set -euo pipefail

BUILD=build

mkdir -p ${BUILD}
pushd ${BUILD}
	cmake ..
	cmake -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug .
	ctest --verbose
popd
