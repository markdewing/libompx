enable_language(CXX)

if (DEFINED LIBOMPX_CUDA_THRUST)
  add_compile_definitions(LIBOMPX_CUDA_THRUST=${LIBOMPX_CUDA_THRUST})
endif (DEFINED LIBOMPX_CUDA_THRUST)


add_library(libompxSortOMP OBJECT sort.cpp)

install(
    TARGETS libompxSortOMP
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

