
#
# Build CUDA backend
#

set(CMAKE_CUDA_COMPILER clang++)
find_package(CUDAToolkit)
enable_language(CUDA)

if (NOT(CUDAToolkit_FOUND))
    message("CUDA toolkit not found")
endif()

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -fgpu-rdc --cuda-gpu-arch=native --offload-new-driver -Xclang -fcuda-allow-variadic-functions")

if (USE_OFFLOAD_LTO)
  set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -foffload-lto")
endif()

find_package(Thrust REQUIRED CONFIG)
thrust_create_target(Thrust)

add_library(ompx sort_impl.cu sort_impl2.cu sort_by_key_impl.cu inclusive_scan_impl.cu)

target_link_libraries(ompx PUBLIC CUDA::cudart)

# Apparently need to add a directory here in order for the target_include_directory in
# the parent CMakeLists.txt to work (??)
target_include_directories(ompx PRIVATE "")
