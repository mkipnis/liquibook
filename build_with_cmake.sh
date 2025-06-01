#!/bin/bash

rm -rf build
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=$HOME
cmake --build build --verbose --target install

CMAKE_ARGS="-DLIQUIBOOK_SRC=`pwd`/src" python3 -m build --wheel python --verbose

unzip -l python/dist/liquibook-1.0.1-cp313-cp313-macosx_15_0_arm64.whl

echo To install: pip3 install python/dist/liquibook-1.0.1-cp313-cp313-macosx_15_0_arm64.whl --break-system-packages --force-reinstall
echo To test: python3 python/basic_order_book_test.py
