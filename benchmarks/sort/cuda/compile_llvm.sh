
clang++ \
-O3 \
-g \
--offload-arch=sm_89 \
cuda_perf_sort.cu \
-L/usr/local/cuda-12.2/lib64 \
-lcuda -lcudart


