
#include "ompx/sort.h"
#include <stdexcept>

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>


namespace ompx {
namespace device {

struct type_size16_t {
  uint8_t tmp_[16];
};

void ompx_sort_cmp(void *B, size_t NumElements, size_t elementSize,
                   ompx_sort_cmp_ty F) {
  switch (elementSize) {
  case 1:
    std::sort(oneapi::dpl::execution::dpcpp_default, (uint8_t *)B, (uint8_t *)B + NumElements,
              [=](uint8_t L, uint8_t R) { return F(&L, &R); });
    break;
  case 2:
    std::sort(oneapi::dpl::execution::dpcpp_default, (uint16_t *)B, (uint16_t *)B + NumElements,
              [=](uint16_t L, uint16_t R) { return F(&L, &R); });
    break;
  case 4:
    std::sort(oneapi::dpl::execution::dpcpp_default, (uint32_t *)B, (uint32_t *)B + NumElements,
              [=](uint32_t L, uint32_t R) { return F(&L, &R); });
    break;
  case 8:
    std::sort(oneapi::dpl::execution::dpcpp_default, (uint64_t *)B, (uint64_t *)B + NumElements,
              [=](uint64_t L, uint64_t R) { return F(&L, &R); });
    break;
  case 16:
    std::sort(oneapi::dpl::execution::dpcpp_default, (type_size16_t *)B, (type_size16_t *)B + NumElements,
              [=](type_size16_t L, type_size16_t R) { return F(&L, &R); });
    break;
  default:
    throw std::runtime_error("ompx_sort data size not handled: " +
                             std::to_string(elementSize));
  };
}

} // namespace device
} // namespace ompx
