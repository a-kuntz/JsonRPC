#!/bin/bash

set -euo pipefail

BUILD_FOLDER=build
BUILD_TYPE=Release

conan install . --install-folder=${BUILD_FOLDER} -pr:b=default -s build_type=${BUILD_TYPE}
cmake -B ${BUILD_FOLDER} -DCMAKE_TOOLCHAIN_FILE=${BUILD_FOLDER}/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DBUILD_TESTS=ON -DBUILD_EXAMPLE=ON
cmake --build ${BUILD_FOLDER}
cd ${BUILD_FOLDER}; ctest --verbose; cd ..
