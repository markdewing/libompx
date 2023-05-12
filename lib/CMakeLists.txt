

if (BUILD_CUDA)
  add_subdirectory(cuda)
endif()

if (BUILD_ROCM)
  add_subdirectory(rocm)
endif()

if (BUILD_ONEAPI)
  add_subdirectory(oneapi)
endif()

if (BUILD_HOST)
  add_subdirectory(host)
endif()
