#!/bin/bash

git diff --name-only master | grep '\.cpp\|\.h' | xargs clang-format -i
