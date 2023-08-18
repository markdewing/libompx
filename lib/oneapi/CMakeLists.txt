
#
# Build OneAPI/sycl backend
#





add_library(ompx sort_impl.cpp)
target_compile_definitions(ompx PUBLIC ONEAPI)

set_target_properties(ompx PROPERTIES COMPILE_OPTIONS "-fsycl;-fiopenmp;-fopenmp-targets=spir64")

