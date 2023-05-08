
#
# Build CUDA backend
#

set(CMAKE_CUDA_COMPILER clang++)
find_package(CUDAToolkit)
enable_language(CUDA)

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -fgpu-rdc --cuda-gpu-arch=native --offload-new-driver -Xclang -fcuda-allow-variadic-functions")


find_package(Thrust REQUIRED CONFIG)
thrust_create_target(Thrust)

add_library(ompx sort_impl.cu)
target_include_directories(ompx PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(ompx Thrust)

install(TARGETS ompx
        EXPORT ompx
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
       )

