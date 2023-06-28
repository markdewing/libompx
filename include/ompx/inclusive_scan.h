#ifndef OMPX_INCLUSIVE_SCAN_H
#define OMPX_INCLUSIVE_SCAN_H

#include <stddef.h>

namespace ompx {

namespace device {

#ifdef ONEAPI
#else
template <typename T1, typename T2>
void ompx_inclusive_scan_n(T1 *in_begin, size_t n, T2 *out_begin);

template <typename T1, typename T2>
void inclusive_scan(T1 *in_begin, T1 *in_end, T2 *out_begin) {
  size_t n = in_end - in_begin;
#pragma omp target data use_device_ptr(in_begin, out_begin)
  ompx::device::ompx_inclusive_scan_n(in_begin, n, out_begin);
}
#endif
} // namespace device
} // namespace ompx

#endif
