cmake_minimum_required(VERSION 3.10)

project(liquibook VERSION 1.0.0)

cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)

if(BUILD_PYTHON)
add_subdirectory(swig)
endif()

install(DIRECTORY src/ DESTINATION include/liquibook
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
)
