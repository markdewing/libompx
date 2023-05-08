#ifndef OMPX_SORT_H
#define OMPX_SORT_H

namespace ompx {
namespace host {

template <typename RandomAccessIterator>
void ompx_sort(RandomAccessIterator first, RandomAccessIterator last);

template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last) {
  ompx::host::ompx_sort(first, last);
}
} // namespace host

namespace device {
template <typename RandomAccessIterator>
void ompx_sort(RandomAccessIterator first, RandomAccessIterator last);

template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last) {
  ompx::device::ompx_sort(first, last);
}
} // namespace device
} // namespace ompx

#endif
