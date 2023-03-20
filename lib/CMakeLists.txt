
#
# Build CUDA backend
#

set(CMAKE_CUDA_COMPILER clang++)
#set(CUDAToolkit_ROOT /usr/local/cuda-11.5)
find_package(CUDAToolkit)
enable_language(CUDA)

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -foffload-lto -fgpu-rdc --cuda-gpu-arch=native --offload-new-driver")
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} --cuda-path=/usr/local/cuda-11.5")


find_package(Thrust REQUIRED CONFIG)
thrust_create_target(Thrust)

add_library(ompx cuda/sort_impl.cu)
#set_target_properties(ompx PROPERTIES CUDA_ARCHITECTURES "61")
target_include_directories(ompx PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(ompx Thrust)

install(TARGETS ompx
        EXPORT ompx
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
       )

