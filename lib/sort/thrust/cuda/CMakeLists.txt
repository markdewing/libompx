find_package(Thrust)

if(NOT Thrust_FOUND)
  message("CUDA Thrust not found, not building libompxSortThrustCUDA")
  return()
endif()

set(LIBOMPX_CUDA_THRUST "1" CACHE "b" PARENT_SCOPE)

add_compile_definitions(LIBOMPX_BACKEND_NAME=cuda)

enable_language(CUDA)

thrust_create_target(Thrust IGNORE_CUB_VERSION_CHECK)

set_source_files_properties(../common/sort.cpp PROPERTIES LANGUAGE CUDA)

add_library(libompxSortThrustCUDA OBJECT ../common/sort.cpp)

target_link_libraries(libompxSortThrustCUDA Thrust)

set_target_properties(libompxSortThrustCUDA PROPERTIES CUDA_ARCHITECTURES "60;70;75;80")

install(
    TARGETS libompxSortThrustCUDA
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
