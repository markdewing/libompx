
#
# Build host backend
#

add_library(ompx_host sort_impl.cpp sort_impl2.cpp)

target_include_directories(ompx_host PUBLIC "${PROJECT_SOURCE_DIR}/include")

install(TARGETS ompx_host
        EXPORT ompx_host
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
       )

