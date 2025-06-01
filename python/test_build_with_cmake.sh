#!/bin/bash

rm -rf build_dir
cmake -S . -B build_dir -DLIQUIBOOK_SRC=../src
cmake --build build_dir --verbose
