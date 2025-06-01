cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)

set(CMAKE_CXX_STANDARD 11)

message(STATUS "System: ${CMAKE_SYSTEM_NAME}")

option(BUILD_PYTHON "Build Python module" ON)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

if(Python_FOUND)

  find_package(SWIG REQUIRED)

  if(SWIG_VERSION VERSION_LESS "3.0.1")
    message(WARNING "SWIG ${SWIG_VERSION} installed, but >= 3.0.1 recommended.")
  endif()

  include(UseSWIG)
  add_compile_options(-DSWIG_BUILD)

  set(CMAKE_SWIG_FLAGS "-py3" "-modern" "-builtin")

  set_source_files_properties(liquibook.i PROPERTIES
    CPLUSPLUS ON SWIG_DIRECTORS ON
    SWIG_OUTPUT_FILE_DIR "${CMAKE_CURRENT_BINARY_DIR}/liquibook"
  )

  swig_add_library(liquibook
    LANGUAGE python
    TYPE MODULE
    SOURCES liquibook.i
  )

  target_include_directories(liquibook PRIVATE ${Python_INCLUDE_DIRS} ${LIQUIBOOK_SRC})
  target_link_libraries(liquibook PRIVATE ${PYTHON_LIBRARIES})
  # uncomment for mac: target_link_libraries(liquibook PRIVATE /opt/homebrew/Frameworks/Python.framework/Versions/Current/lib/libpython3.13.dylib)

  add_custom_command(TARGET liquibook POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/liquibook"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_BINARY_DIR}/liquibook.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/liquibook/liquibook.py"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:liquibook>"
    "${CMAKE_CURRENT_SOURCE_DIR}/liquibook/$<TARGET_FILE_NAME:liquibook>"
  COMMENT "Copying SWIG-generated Python files to source folder"
  )

endif()
