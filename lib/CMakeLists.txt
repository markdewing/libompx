

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

target_include_directories(ompx
       PUBLIC
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS ompx
        EXPORT ompx
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
       )
