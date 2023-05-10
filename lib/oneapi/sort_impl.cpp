
#include "ompx/sort.h"
#include <stdexcept>

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace ompx {
namespace device {

template <typename T> void ompx_sort(T B, size_t NumElements) {
  std::sort(oneapi::dpl::execution::dpcpp_default, B, B+NumElements);
}

#include "../inst/sort_inst.h"

} // namespace device
} // namespace ompx
