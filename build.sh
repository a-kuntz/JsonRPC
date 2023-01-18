#!/bin/bash

set -x
set -euo pipefail

BUILD_TYPE=${1:-Release}
BUILD_FOLDER=build-${BUILD_TYPE}

conan install . --install-folder=${BUILD_FOLDER} -pr:b=default -s build_type=${BUILD_TYPE} --build=missing
cmake -B ${BUILD_FOLDER} -DCMAKE_TOOLCHAIN_FILE=${BUILD_FOLDER}/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
cmake --build ${BUILD_FOLDER}

pushd ${BUILD_FOLDER}
	ctest --verbose
popd
