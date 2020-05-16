#!/bin/bash

set -euo pipefail

BUILD=build

mkdir -p ${BUILD}
pushd ${BUILD}
	conan install ..
	cmake .. \
		-DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake
	CTEST_OUTPUT_ON_FAILURE=1 \
		make all test VERBOSE=1
popd
