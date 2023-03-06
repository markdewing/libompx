cmake_minimum_required(VERSION 3.20)

project(libompx VERSION "0.1" DESCRIPTION "LIBOMPX")

enable_testing()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(lib)
add_subdirectory(tests)

# Installation

include(GNUInstallDirs)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ompx DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
