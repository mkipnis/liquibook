
cmake_minimum_required(VERSION 3.28)

project(liquibook VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_PYTHON "Build Python bindings using pybind11" OFF)

# Install C++ headers.
install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/src/"
    DESTINATION include/liquibook
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
)

# Build Python bindings if requested.
if(BUILD_PYTHON)
    add_subdirectory(python)
endif()
