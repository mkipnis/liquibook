#!/bin/bash

cmake -S . -B build -DCMAKE_INSTALL_PREFIX=$HOME -DBUILD_PYTHON=ON
#cmake -S . -B build -DCMAKE_INSTALL_PREFIX=$HOME #-DBUILD_PYTHON=ON
cmake --build build --verbose --target install
