# Only build Python bindings if requested by the top-level project.
if(BUILD_PYTHON)

    # Find Python interpreter and development module support.
    find_package(
        Python3 REQUIRED
        COMPONENTS Interpreter Development.Module
    )

    # Find pybind11. Support installations made through pip.
    find_package(pybind11 CONFIG QUIET)

    if(NOT pybind11_FOUND)
        execute_process(
            COMMAND "${Python3_EXECUTABLE}" -m pybind11 --cmakedir
            OUTPUT_VARIABLE pybind11_DIR
            OUTPUT_STRIP_TRAILING_WHITESPACE
            RESULT_VARIABLE pybind11_RESULT
        )

        if(NOT pybind11_RESULT EQUAL 0)
            message(FATAL_ERROR
                "pybind11 was not found. Install it with:\n"
                "  ${Python3_EXECUTABLE} -m pip install pybind11"
            )
        endif()

        find_package(pybind11 CONFIG REQUIRED
            PATHS "${pybind11_DIR}"
            NO_DEFAULT_PATH
        )
    endif()

    # Build the native Python extension.
    # The target name must match PYBIND11_MODULE(liquibook, m).
    pybind11_add_module(liquibook MODULE
        liquibook_pybind.cpp
    )

    target_compile_features(liquibook PRIVATE cxx_std_17)

    # LiquiBook headers.
    target_include_directories(liquibook PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
    )

    # The original SWIG interface included simple_order.cpp directly.
    # Compile it here if its implementation is not already provided
    # by a linked LiquiBook library.
    target_sources(liquibook PRIVATE
        "${PROJECT_SOURCE_DIR}/src/simple/simple_order.cpp"
    )

    # Install the compiled extension.
    # LIBRARY covers Linux/macOS; RUNTIME covers Windows.
    install(TARGETS liquibook
        LIBRARY DESTINATION liquibook
        RUNTIME DESTINATION liquibook
    )

endif()

