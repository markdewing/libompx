
LIBOMPX_BUILD=../../../../build_cuda/lib/cuda

clang++  \
-O3 \
-g \
-fopenmp \
-fopenmp-targets=nvptx64 \
-I../../../include/ \
--cuda-gpu-arch=native \
perf_sort.cpp \
-L${LIBOMPX_BUILD} -lompx \
-L/usr/local/cuda-12.2/lib64 -lcuda -lcudart
