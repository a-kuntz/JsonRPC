#!/bin/bash

set -euo pipefail

BUILD=build

mkdir -p ${BUILD}
pushd ${BUILD}
	cmake ..
	cmake --build .
	ctest --verbose
popd
