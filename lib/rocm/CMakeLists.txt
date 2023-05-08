
#
# Build ROCM backend
#

set(CMAKE_HIP_COMPILER clang++)
find_package(hip)

set(CMAKE_HIP_FLAGS "${CMAKE_CUDA_FLAGS} --offload-arch=native")


find_package(rocthrust REQUIRED)

add_library(ompx sort_impl.cpp)

get_property(hip_compile_opts TARGET hip::device PROPERTY INTERFACE_COMPILE_OPTIONS)
set(hip_compile_opts "${hip_compile_opts} --offload-arch=native")
target_compile_options(ompx PRIVATE "${hip_compile_opts}")

target_include_directories(ompx PRIVATE "${ROCTHRUST_INCLUDE_DIR}")
target_include_directories(ompx PUBLIC "${PROJECT_SOURCE_DIR}/include")

install(TARGETS ompx
        EXPORT ompx
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
       )

