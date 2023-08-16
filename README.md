
# Libompx

Libompx is a cross platform portability library for OpenMP offload.


# Example

This piece of code will call the sort function on the device.

```
#include <ompx/sort.h>

int main()
{
    const int N = 10;
    int* values = new int[N];

#pragma omp target enter data map(to: values[:N])
    ompx::device::sort(values, values + N);
#pragma omp target exit data map(from: values[:N])
}
```

For CUDA or ROCm backends, compile with
```
clang++ -fopenmp --offload-arch=native -I<path to libompx install>/include tmp.cpp  -L<path to libompx install>/lib -lompx
```
Platform specific libraries may also need to linked (`-lcuda -lcudart` for CUDA and `-lamdhip64` for ROCm).

For OneAPI, compile with
```
icpx -fsycl -fiopenmp -fopenmp-targets=spir64 -D ONEAPI -I<path to libompx install>/include tmp.cpp
```


# Installing

CMake is used for configuration and build.
The library uses [Catch2](https://github.com/catchorg/Catch2) for unit testing.

### CMake Build Options

Choose and enable one of the backends:
* `LIBOMPX_BUILD_CUDA` - enable CUDA
* `LIBOMPX_BUILD_ROCM` - enable ROCm
* `LIBOMPX_BUILD_ONEAPI` - enable OneAPI

A host CPU backend is optional
* `LIBOMPX_BUILD_HOST` - enable host CPU backend

Offload link-time-optimization (LTO) can be enabled (for CUDA and ROCm backends)
* `LIBOMPX_USE_OFFLOAD_LTO` - use `-foffload-lto` compiler option

Tests (and the use the Catch2 library) can be configured with
* `LIBOMPX_BUILD_TESTS` - enable unit tests
