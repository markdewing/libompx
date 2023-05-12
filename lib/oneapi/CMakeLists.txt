
#
# Build OneAPI/sycl backend
#





add_library(ompx sort_impl.cpp sort_impl2.cpp)
target_include_directories(ompx PUBLIC "${PROJECT_SOURCE_DIR}/include")

set_target_properties(ompx PROPERTIES COMPILE_OPTIONS "-fsycl;-fiopenmp;-fopenmp-targets=spir64;-fsycl-enable-function-pointers")



install(TARGETS ompx
        EXPORT ompx
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
       )

