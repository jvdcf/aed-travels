cmake_minimum_required(VERSION 3.26)
project(AED2324_PRJ2_G23)

set(CMAKE_CXX_STANDARD 20)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

# Project build
add_executable(finsc main.cpp
        lib/Graph.h
        src/data/Airport.cpp src/data/Airport.hpp
        src/data/Airline.cpp src/data/Airline.hpp
        src/data/Data.cpp src/data/Data.hpp
        src/Parser.cpp src/Parser.hpp
        src/Runtime.cpp src/Runtime.hpp
        src/Utils.hpp src/Utils.cpp)
