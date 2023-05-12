
#include "ompx/sort.h"
#include <stdexcept>

#include <algorithm>

namespace ompx {
namespace host {

template <typename T> void ompx_sort(T B, size_t NumElements) {
  std::sort(B, B + NumElements);
}

#include "../inst/sort_inst.h"

} // namespace host
} // namespace ompx
