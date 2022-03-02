add_subdirectory(omp)
add_subdirectory(thrust)

add_library(libompxSort
  $<TARGET_OBJECTS:libompxSortThrustCUDA>
  $<TARGET_OBJECTS:libompxSortOMP>)
#target_link_libraries(libompxSort )
#target_link_libraries(libompxSort $<TARGET_OBJECTS:libompxSortOMP>)

install(
    TARGETS libompxSort
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

