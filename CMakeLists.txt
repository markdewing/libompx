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
include(CMakePackageConfigHelpers)

# File with target information
install(EXPORT ompx
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libompx
    NAMESPACE libompx::
    FILE libompxTargets.cmake
)

# File that can be used from the build directory (and is not installed)
export(EXPORT ompx
    FILE ${CMAKE_INSTALL_LIBDIR}/cmake/libompx/libompxTargets.cmake
    NAMESPACE libompx::
)

# https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html#creating-packages
# Package file
if (LIBOMPX_BUILD_CUDA)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config_cuda.cmake.in
     "${CMAKE_CURRENT_BINARY_DIR}/libompxConfig.cmake"
     INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libompx)
endif()

if (LIBOMPX_BUILD_ROCM)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config_rocm.cmake.in
     "${CMAKE_CURRENT_BINARY_DIR}/libompxConfig.cmake"
     INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libompx)
endif()

if (LIBOMPX_BUILD_ONEAPI)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config_oneapi.cmake.in
     "${CMAKE_CURRENT_BINARY_DIR}/libompxConfig.cmake"
     INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libompx)
endif()

# Version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/libompxConfigVersion.cmake"
    VERSION "${version}"
    COMPATIBILITY AnyNewerVersion
    )

# Put package and version files in the install location
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/libompxConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/libompxConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libompx)


add_library(libompx::ompx ALIAS ompx)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ompx DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
