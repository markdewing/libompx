cmake_minimum_required(VERSION 3.20)

project(libompx VERSION "0.1" DESCRIPTION "LIBOMPX")

enable_testing()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
# C++ extensions off to avoid "error: __float128 is not supported on this target"
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(lib)
add_subdirectory(tests)

# Installation

include(GNUInstallDirs)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ompx DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
