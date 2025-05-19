cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)

set(CMAKE_CXX_STANDARD 11)

# Determine system type (uname)
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")

# Check for SWIG
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

if(SWIG_VERSION VERSION_LESS "3.0.1")
  message(WARNING "You have SWIG ${SWIG_VERSION} installed, but at least SWIG 3.0.1 is recommended. Some features may not work.")
endif()

# Check for Python and enable/disable Python bindings
option(BUILD_PYTHON "Build Python module" ON)

if(BUILD_PYTHON)
  find_package(Python3 COMPONENTS Interpreter Development)
  if(Python3_FOUND)
    message(STATUS "Python3 found: ${Python3_EXECUTABLE}")
    include_directories(${Python3_INCLUDE_DIRS})
    set(HAVE_PYTHON TRUE)
  else()
    message(WARNING "Python3 not found, disabling Python bindings")
    set(BUILD_PYTHON OFF)
  endif()
endif()

# Shared library flags depending on platform
if(APPLE)
  set(SHARED_LIB "-dynamiclib")
  set(SHARED_LIB_EXTENSION "dylib")
else()
  set(SHARED_LIB "-shared")
  set(SHARED_LIB_EXTENSION "so")
endif()

# === Configure setup.py from template ===
if(BUILD_PYTHON AND Python3_FOUND)

  add_compile_options(-DSWIG_BUILD)

  set(SWIG_INTERFACE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/liquibook.i")
  set_source_files_properties(${SWIG_INTERFACE_FILE} PROPERTIES CPLUSPLUS ON)

  swig_add_library(liquibook LANGUAGE python SOURCES ${SWIG_INTERFACE_FILE})
  target_include_directories(${SWIG_MODULE_liquibook_REAL_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src ${Python3_INCLUDE_DIRS})
  target_link_libraries(${SWIG_MODULE_liquibook_REAL_NAME} PRIVATE ${Python3_LIBRARIES})

  file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/python/liquibook")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/python/liquibook/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/python/liquibook")

  configure_file( "${CMAKE_CURRENT_SOURCE_DIR}/python/setup.py.in" "${CMAKE_CURRENT_BINARY_DIR}/python/setup.py" @ONLY)

  # Build Python module using setup.py
  add_custom_target(
  build_python ALL
  COMMAND ${Python3_EXECUTABLE} setup.py build
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/python"
  DEPENDS ${SWIG_MODULE_liquibook_REAL_NAME} "${CMAKE_CURRENT_BINARY_DIR}/python/setup.py"
  COMMENT "Building Python bindings via setup.py"
)

  # Optional install target
add_custom_target(
  install_python
  COMMAND "${Python3_EXECUTABLE}" setup.py install --prefix="${CMAKE_INSTALL_PREFIX}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/python"
  DEPENDS build_python
  COMMENT "Installing Python bindings"
)

set(PYTHON_PACKAGE_NAME ${PROJECT_NAME})
set(PYTHON_PACKAGE_VERSION ${PROJECT_VERSION})
set(WHEEL_FILE_NAME "${PYTHON_PACKAGE_NAME}-${PYTHON_PACKAGE_VERSION}-py3-none-any.whl")
set(WHEEL_FILE_PATH "${CMAKE_CURRENT_BINARY_DIR}/dist/${WHEEL_FILE_NAME}")

add_custom_command(
  OUTPUT ${WHEEL_FILE_PATH}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/python
  COMMAND ${Python3_EXECUTABLE} setup.py bdist_wheel
  COMMENT "Building wheel package"
)

add_custom_target(build_wheel ALL
  DEPENDS ${WHEEL_FILE_PATH}
)

add_custom_target(install_wheel
  COMMAND ${Python3_EXECUTABLE} -m pip install --force-reinstall ${WHEEL_FILE_PATH}
  DEPENDS build_wheel
  COMMENT "Installing Python wheel"
)

endif()
