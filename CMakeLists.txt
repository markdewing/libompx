cmake_minimum_required(VERSION 3.20)

project(libompx VERSION "0.1" DESCRIPTION "LIBOMPX")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(lib)

# Installation

include(GNUInstallDirs)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ompx DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
