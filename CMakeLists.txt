cmake_minimum_required(VERSION 3.20)

project(libompx VERSION "0.1" DESCRIPTION "LIBOMPX")

include_directories(include)

#add_library(libompx lib/sort/thrust/)

# Add path for custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib)
