
#include "ompx/sort.h"
#include <stdexcept>

#include "thrust/sort.h"

namespace ompx {
namespace device {

struct type_size16_t {
  uint8_t tmp_[16];
};

void ompx_sort_impl(void *B, void *E, int size, ompx_sort_cmp_ty F) {
  switch (size) {
  case 1:
    thrust::sort(thrust::device, (uint8_t *)B, (uint8_t *)E,
                 [=](uint8_t L, uint8_t R) { return F(&L, &R); });
    break;
  case 2:
    thrust::sort(thrust::device, (uint16_t *)B, (uint16_t *)E,
                 [=](uint16_t L, uint16_t R) { return F(&L, &R); });
    break;
  case 4:
    thrust::sort(thrust::device, (uint32_t *)B, (uint32_t *)E,
                 [=](uint32_t L, uint32_t R) { return F(&L, &R); });
    break;
  case 8:
    thrust::sort(thrust::device, (uint64_t *)B, (uint64_t *)E,
                 [=](uint64_t L, uint64_t R) { return F(&L, &R); });
    break;
  case 16:
    thrust::sort(thrust::device, (type_size16_t *)B, (type_size16_t *)E,
                 [=](type_size16_t L, type_size16_t R) { return F(&L, &R); });
    break;
  default:
    // printf("Error, size %i not handled\n", size);
    throw std::runtime_error("ompx_sort data size not handled: " +
                             std::to_string(size));
  };
}
} // namespace device
} // namespace ompx
