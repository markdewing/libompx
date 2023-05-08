
// Work around for gcc 12 include files in CUDA mode.
// Clang was fixed to recognize __noinline__ as an attribute,
// but the CUDA include files still have a define for __noinline__.
// The attribute started to be used in gcc 12 include files, which expands
// to __attribute__((__attribute__((noinline)))), which the compiler rejects.
// See https://github.com/NVIDIA/thrust/issues/1703 and
//     https://github.com/llvm/llvm-project/issues/57544
#undef __noinline__

#include "ompx/sort.h"
#include <stdexcept>

#include "thrust/sort.h"

namespace ompx {
namespace device {

template <typename T>
void ompx_sort(T B, T E)
{
    thrust::sort(thrust::device, B, E);
}

template void ompx_sort(int*, int*);


} // namespace device
} // namespace ompx
