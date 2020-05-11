#!/bin/bash

for DIR in lib app test
do
	find ${DIR} -name "*.cpp" -o -name "*.h" | xargs clang-format -i
done
