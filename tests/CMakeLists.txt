
set(OFFLOAD_COMPILE_OPTIONS -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -Xopenmp-target=nvptx64 -fopenmp-offload-mandatory)
set(OFFLOAD_COMPILE_OPTIONS ${OFFLOAD_COMPILE_OPTIONS} -foffload-lto -fgpu-rdc)


add_executable(test_sort test_sort.cpp)
target_include_directories(test_sort PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(test_sort PRIVATE ompx)
target_compile_options(test_sort PRIVATE ${OFFLOAD_COMPILE_OPTIONS})
target_link_options(test_sort PRIVATE ${OFFLOAD_COMPILE_OPTIONS})

target_link_options(test_sort PRIVATE -L${CUDAToolkit_BIN_DIR}/../lib64)

# Would like to get these forwarded from ompx, but cmake is putting them before libompx
target_link_libraries(test_sort PRIVATE -lcuda -lcudart)


add_test(NAME test_sort COMMAND test_sort)

