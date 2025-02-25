

find_package(Catch2 3 REQUIRED)

if (LIBOMPX_BUILD_CUDA)
  set(OFFLOAD_COMPILE_OPTIONS -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -fopenmp-offload-mandatory)
  set(OFFLOAD_COMPILE_OPTIONS ${OFFLOAD_COMPILE_OPTIONS} -fgpu-rdc)
endif()

if (LIBOMPX_BUILD_ROCM)
  set(OFFLOAD_COMPILE_OPTIONS -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -fopenmp-offload-mandatory)
  set(OFFLOAD_COMPILE_OPTIONS ${OFFLOAD_COMPILE_OPTIONS} -fgpu-rdc)
endif()

if (LIBOMPX_USE_OFFLOAD_LTO)
  set(OFFLOAD_COMPILE_OPTIONS ${OFFLOAD_COMPILE_OPTIONS} -foffload-lto)
endif()

if (LIBOMPX_BUILD_ONEAPI)
  set(OFFLOAD_COMPILE_OPTIONS -fiopenmp -fsycl -fopenmp-targets=spir64)
endif()


set(tests test_sort test_sort_cmp test_sort_by_key test_inclusive_scan)

foreach(test IN LISTS tests)
  add_executable(${test} ${test}.cpp)
  target_include_directories(${test} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

  target_link_libraries(${test} PRIVATE ompx)
  target_link_libraries(${test} PRIVATE Catch2::Catch2WithMain)
  target_compile_options(${test} PRIVATE ${OFFLOAD_COMPILE_OPTIONS})
  target_link_options(${test} PRIVATE ${OFFLOAD_COMPILE_OPTIONS})

  add_test(NAME ${test} COMMAND ${test})
endforeach()

if (LIBOMPX_BUILD_HOST)
  set(host_tests test_host_sort test_host_sort_cmp)

  foreach(test IN LISTS host_tests)
    add_executable(${test} ${test}.cpp)
    target_include_directories(${test} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

    target_link_libraries(${test} PRIVATE ompx_host)
    target_link_libraries(${test} PRIVATE Catch2::Catch2WithMain)

    add_test(NAME ${test} COMMAND ${test})
  endforeach()
endif()
