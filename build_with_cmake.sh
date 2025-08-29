#!/bin/bash

rm -rf build
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=$HOME
cmake --build build --target install

# Build wheel via scikit-build / pyproject.toml
CMAKE_ARGS="-DLIQUIBOOK_SRC=$(pwd)/src -DBUILD_PYTHON=ON" python3 -m build --wheel --verbose

echo To install: pip3 install dist/* --break-system-packages --force-reinstall
echo To test: python3 python/examples/BasicOrderBookTest/basic_order_book_test.py
