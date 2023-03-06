
#include "thrust/sort.h"

namespace ompx {
namespace host {

template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last) {
  thrust::sort(thrust::host, first, last);
}

template <typename RandomAccessIterator>
void stable_sort(RandomAccessIterator first, RandomAccessIterator last) {
  thrust::stable_sort(thrust::host, first, last);
}

template <typename RandomAccessIterator1, typename RandomAccessIterator2>
void sort_by_key(RandomAccessIterator1 keys_first,
                 RandomAccessIterator1 keys_last,
                 RandomAccessIterator2 values_first) {
  thrust::sort_by_key(thrust::host, keys_first, keys_last, values_first);
}

template <typename RandomAccessIterator1, typename RandomAccessIterator2>
void stable_sort_by_key(RandomAccessIterator1 keys_first,
                        RandomAccessIterator1 keys_last,
                        RandomAccessIterator2 values_first) {
  thrust::stable_sort_by_key(thrust::host, keys_first, keys_last, values_first);
}

} // namespace host

namespace device {

template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last) {
  thrust::sort(thrust::device, first, last);
}

template <typename RandomAccessIterator>
void stable_sort(RandomAccessIterator first, RandomAccessIterator last) {
  thrust::stable_sort(thrust::device, first, last);
}

template <typename RandomAccessIterator1, typename RandomAccessIterator2>
void sort_by_key(RandomAccessIterator1 keys_first,
                 RandomAccessIterator1 keys_last,
                 RandomAccessIterator2 values_first) {
  thrust::sort_by_key(thrust::device, keys_first, keys_last, values_first);
}

template <typename RandomAccessIterator1, typename RandomAccessIterator2>
void stable_sort_by_key(RandomAccessIterator1 keys_first,
                        RandomAccessIterator1 keys_last,
                        RandomAccessIterator2 values_first) {
  thrust::stable_sort_by_key(thrust::device, keys_first, keys_last,
                             values_first);
}

} // namespace device
} // namespace ompx
// Explicit instantiations
template void ompx::host::sort(int *, int *);
template void ompx::host::stable_sort(int *, int *);
template void ompx::host::sort_by_key(int *, int *, double *);
template void ompx::host::sort_by_key(int *, int *, int *);
template void ompx::host::stable_sort_by_key(int *, int *, double *);
template void ompx::host::stable_sort_by_key(int *, int *, int *);
template void ompx::device::sort(int *, int *);
template void ompx::device::stable_sort(int *, int *);
template void ompx::device::sort_by_key(int *, int *, double *);
template void ompx::device::sort_by_key(int *, int *, int *);
template void ompx::device::stable_sort_by_key(int *, int *, double *);
template void ompx::device::stable_sort_by_key(int *, int *, int *);
