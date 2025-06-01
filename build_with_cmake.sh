#!/bin/bash

rm -rf build
cmake -B build -S . -DCMAKE_INSTALL_PREFIX=$HOME
cmake --build build --verbose --target install

# To install on ubuntu
#python3 -m pip install --upgrade build
# sudo apt-get install swig
CMAKE_ARGS="-DLIQUIBOOK_SRC=`pwd`/src" python3 -m build --wheel python --verbose

unzip -l python/dist/*

echo To install: pip3 install python/dist/*  --break-system-packages --force-reinstall
echo To test: python3 python/basic_order_book_test.py
