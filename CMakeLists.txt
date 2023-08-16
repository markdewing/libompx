cmake_minimum_required(VERSION 3.20)

project(libompx VERSION "0.2" DESCRIPTION "LIBOMPX")

enable_testing()

option(LIBOMPX_BUILD_CUDA "Enable CUDA backend" OFF)
option(LIBOMPX_BUILD_ROCM "Enable ROCm backend" OFF)
option(LIBOMPX_BUILD_ONEAPI "Enable OneAPI backend" OFF)
option(LIBOMPX_BUILD_HOST "Enable host CPU library" OFF)

option(LIBOMPX_USE_OFFLOAD_LTO  "Enable Offload Link Time Optimization (LTO)" OFF)

option(LIBOMPX_BUILD_TESTS "Enable tests" ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 17)
# C++ extensions off to avoid "error: __float128 is not supported on this target"
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(lib)

if (LIBOMPX_BUILD_TESTS)
  add_subdirectory(tests)
endif()

# Installation

include(GNUInstallDirs)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ompx DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
