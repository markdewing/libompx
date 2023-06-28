
#include "thrust/execution_policy.h"
#include "thrust/scan.h"

namespace ompx {
namespace device {

template <typename T1, typename T2>
void ompx_inclusive_scan_n(T1 *in_begin, size_t n, T2 *out_begin) {
  thrust::inclusive_scan(thrust::device, in_begin, in_begin + n, out_begin);
}

#include "../inst/scan_inst.h"
} // namespace device
} // namespace ompx
