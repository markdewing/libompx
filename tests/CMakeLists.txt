
if (BUILD_CUDA)
  set(OFFLOAD_COMPILE_OPTIONS -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -fopenmp-offload-mandatory)
endif()

if (BUILD_ROCM)
  set(OFFLOAD_COMPILE_OPTIONS -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -fopenmp-offload-mandatory)
endif()

set(OFFLOAD_COMPILE_OPTIONS ${OFFLOAD_COMPILE_OPTIONS} -foffload-lto -fgpu-rdc)


add_executable(test_sort test_sort.cpp)
target_include_directories(test_sort PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(test_sort PRIVATE ompx)
target_compile_options(test_sort PRIVATE ${OFFLOAD_COMPILE_OPTIONS})
target_link_options(test_sort PRIVATE ${OFFLOAD_COMPILE_OPTIONS})


# Would like to get these forwarded from ompx, but cmake is putting them before libompx
if (BUILD_CUDA)
  target_link_options(test_sort PRIVATE -L${CUDAToolkit_BIN_DIR}/../lib64)
  target_link_libraries(test_sort PRIVATE -lcuda -lcudart)
endif()
if (BUILD_ROCM)
  target_link_options(test_sort PRIVATE -L/opt/rocm/lib)
  target_link_libraries(test_sort PRIVATE -lamdhip64)
endif()


add_test(NAME test_sort COMMAND test_sort)

