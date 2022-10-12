#!/bin/bash

set -euo pipefail

BUILD=build

conan install . --install-folder=${BUILD} # -pr:b=default -s build_type=Debug

mkdir -p ${BUILD}
pushd ${BUILD}
	cmake ..
	cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug .
	ctest --verbose
popd
