

if (LIBOMPX_BUILD_CUDA)
  add_subdirectory(cuda)
endif()

if (LIBOMPX_BUILD_ROCM)
  add_subdirectory(rocm)
endif()

if (LIBOMPX_BUILD_ONEAPI)
  add_subdirectory(oneapi)
endif()

if (LIBOMPX_BUILD_HOST)
  add_subdirectory(host)
endif()
