
// Work around for gcc 12 include files in CUDA mode.
// Clang was fixed to recognize __noinline__ as an attribute,
// but the CUDA include files still have a define for __noinline__.
// The attribute started to be used in gcc 12 include files, which expands
// to __attribute__((__attribute__((noinline)))), which the compiler rejects.
// See https://github.com/NVIDIA/thrust/issues/1703 and
//     https://github.com/llvm/llvm-project/issues/57544
#undef __noinline__

#include "thrust/sort.h"

namespace ompx {
namespace device {

template <typename T1, typename T2>
void ompx_sort_by_key(T1 *B, size_t NumElements, T2 *V) {
  thrust::sort_by_key(thrust::device, B, B + NumElements, V);
}

#include "../inst/sort_by_key_inst.h"

} // namespace device
} // namespace ompx
