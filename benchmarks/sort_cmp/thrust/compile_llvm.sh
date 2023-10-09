
clang++ \
-O3 \
-g \
--offload-arch=gfx900 \
-L/opt/rocm-5.6.0/lib -lamdhip64 \
-x hip \
thrust_perf_sort_cmp.cpp \

#--offload-arch=sm_89 \
#-L/usr/local/cuda-12.2/lib64 \
#-lcuda -lcudart

#--offload-arch=sm_89 \

