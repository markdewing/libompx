#ifndef OMPX_SORT_H
#define OMPX_SORT_H

#include <stddef.h>

namespace ompx {
namespace host {

template <typename RandomAccessIterator>
void ompx_sort(RandomAccessIterator first, size_t NumElements);

template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last) {
  size_t NumElements = last - first;
  ompx::host::ompx_sort(first, NumElements);
}
} // namespace host

namespace device {
template <typename RandomAccessIterator>
void ompx_sort(RandomAccessIterator first, size_t NumElements);

template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last) {
  size_t NumElements = last - first;
#pragma omp target data use_device_ptr(first)
  ompx::device::ompx_sort(first, NumElements);
}
} // namespace device
} // namespace ompx

#endif
