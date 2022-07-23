

#
# Build CUDA backend
# 

enable_language(CUDA)

add_library(ompx cuda/sort.cu)
set_target_properties(ompx PROPERTIES CUDA_ARCHITECTURES "61")

find_package(CUB REQUIRED CONFIG)
find_package(Thrust REQUIRED CONFIG)
target_link_libraries(ompx PRIVATE Thrust)
target_link_options(ompx PUBLIC -lcuda -lcudart)

install(TARGETS ompx
        EXPORT ompx
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
       ) 

