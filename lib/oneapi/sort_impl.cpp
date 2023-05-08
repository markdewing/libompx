
#include "ompx/sort.h"
#include <stdexcept>

#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>

namespace ompx {
namespace device {

template <typename T> void ompx_sort(T B, T E) {
  std::sort(oneapi::dpl::execution::dpcpp_default, B, E);
}

template void ompx_sort(int *, int *);

} // namespace device
} // namespace ompx
