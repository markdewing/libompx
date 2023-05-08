
#
# Build OneAPI/sycl backend
#





add_library(ompx sort_impl.cpp)
target_include_directories(ompx PUBLIC "${PROJECT_SOURCE_DIR}/include")

set_target_properties(ompx PROPERTIES COMPILE_OPTIONS -fsycl)



install(TARGETS ompx
        EXPORT ompx
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
       )

