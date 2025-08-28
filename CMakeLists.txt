cmake_minimum_required(VERSION 3.15)

project(liquibook VERSION 1.0.1 LANGUAGES CXX)

# Option to build Python bindings
option(BUILD_PYTHON "Build Python bindings using SWIG" OFF)

# Install headers
install(
    DIRECTORY src/
    DESTINATION include/liquibook
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)
