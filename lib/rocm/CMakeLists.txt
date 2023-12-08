
#
# Build ROCM backend
#

set(CMAKE_HIP_COMPILER clang++)
find_package(hip)

set(CMAKE_HIP_FLAGS "${CMAKE_CUDA_FLAGS} --offload-arch=native")


find_package(rocthrust REQUIRED)

add_library(ompx sort_impl.cpp sort_impl2.cpp sort_by_key_impl.cpp inclusive_scan_impl.cpp)

get_property(hip_compile_opts TARGET hip::device PROPERTY INTERFACE_COMPILE_OPTIONS)
set(hip_compile_opts "${hip_compile_opts} --offload-arch=native")
if (USE_OFFLOAD_LTO)
  set(hip_compile_opts "${hip_compile_opts} -foffload-lto")
endif()
target_compile_options(ompx PRIVATE "${hip_compile_opts}")
target_link_libraries(ompx PUBLIC hip::amdhip64)


target_include_directories(ompx PRIVATE "${ROCTHRUST_INCLUDE_DIR}")
