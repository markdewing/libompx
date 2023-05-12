if (BUILD_CUDA)
  set(OFFLOAD_COMPILE_OPTIONS -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -fopenmp-offload-mandatory)
  set(OFFLOAD_COMPILE_OPTIONS ${OFFLOAD_COMPILE_OPTIONS} -fgpu-rdc)
endif()

if (BUILD_ROCM)
  set(OFFLOAD_COMPILE_OPTIONS -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -fopenmp-offload-mandatory)
  set(OFFLOAD_COMPILE_OPTIONS ${OFFLOAD_COMPILE_OPTIONS} -fgpu-rdc)
endif()

if (BUILD_ONEAPI)
  set(OFFLOAD_COMPILE_OPTIONS -fiopenmp -fsycl -fopenmp-targets=spir64)
endif()


set(tests "test_sort")

foreach(test IN LISTS tests)
  add_executable(${test} ${test}.cpp)
  target_include_directories(${test} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

  target_link_libraries(${test} PRIVATE ompx)
  target_compile_options(${test} PRIVATE ${OFFLOAD_COMPILE_OPTIONS})
  target_link_options(${test} PRIVATE ${OFFLOAD_COMPILE_OPTIONS})

  # Would like to get these forwarded from ompx, but cmake is putting them before libompx
  if (BUILD_CUDA)
    target_link_options(${test} PRIVATE -L${CUDAToolkit_BIN_DIR}/../lib64)
    target_link_libraries(${test} PRIVATE -lcuda -lcudart)
  endif()
  if (BUILD_ROCM)
    target_link_options(${test} PRIVATE -L$ENV{ROCM_PATH}/lib)
    target_link_libraries(${test} PRIVATE -lamdhip64)
  endif()

  add_test(NAME ${test} COMMAND ${test})
endforeach()

if (BUILD_HOST)
  set(host_tests "test_host_sort")

  foreach(test IN LISTS host_tests)
    add_executable(${test} ${test}.cpp)
    target_include_directories(${test} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    target_link_libraries(${test} PRIVATE ompx_host)

    add_test(NAME ${test} COMMAND ${test})
  endforeach()
endif()
