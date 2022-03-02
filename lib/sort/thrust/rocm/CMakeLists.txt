# On ROCm rocThrust requires rocPRIM
find_package(rocprim CONFIG PATHS "/opt/rocm/rocprim")

if(NOT rocprim_FOUND)
  message("ROCm prim not found, not building libompxSortThrustROCM")
  return()
endif()

# "/opt/rocm" - default install prefix
find_package(rocthrust CONFIG PATHS "/opt/rocm/rocthrust")

if(NOT rocthrust_FOUND)
  message("ROCm Thrust not found, not building libompxSortThrustROCM")
  return()
endif()

add_library(libompxSortThrustROCM ../common/sort.cpp)

target_link_libraries(libompxSortThrustROCM roc::rocthrust)

install(
    TARGETS libompxSortThrustROCM
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
