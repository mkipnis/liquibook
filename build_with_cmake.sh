#!/bin/bash

rm -rf build
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=$HOME
cmake --build build --verbose --target install

CMAKE_ARGS="-DLIQUIBOOK_SRC=`pwd`/src" python3 -m build --wheel python --verbose

unzip -l python/dist/*

echo To install: pip3 install python/dist/* --break-system-packages --force-reinstall
echo To test: python3 python/examples/BasicOrderBookTest/basic_order_book_test.py
