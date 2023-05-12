
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

struct type_size16_t {
  uint8_t tmp_[16];
};

void ompx_sort_cmp(void *B, size_t NumElements, size_t elementSize,
                   ompx_sort_cmp_ty F) {
  switch (elementSize) {
  case 1:
    thrust::sort(thrust::device, (uint8_t *)B, (uint8_t *)B + NumElements,
                 [=](uint8_t L, uint8_t R) { return F(&L, &R); });
    break;
  case 2:
    thrust::sort(thrust::device, (uint16_t *)B, (uint16_t *)B + NumElements,
                 [=](uint16_t L, uint16_t R) { return F(&L, &R); });
    break;
  case 4:
    thrust::sort(thrust::device, (uint32_t *)B, (uint32_t *)B + NumElements,
                 [=](uint32_t L, uint32_t R) { return F(&L, &R); });
    break;
  case 8:
    thrust::sort(thrust::device, (uint64_t *)B, (uint64_t *)B + NumElements,
                 [=](uint64_t L, uint64_t R) { return F(&L, &R); });
    break;
  case 16:
    thrust::sort(thrust::device, (type_size16_t *)B,
                 (type_size16_t *)B + NumElements,
                 [=](type_size16_t L, type_size16_t R) { return F(&L, &R); });
    break;
  default:
    throw std::runtime_error("ompx_sort data size not handled: " +
                             std::to_string(elementSize));
  };
}

} // namespace device
} // namespace ompx
