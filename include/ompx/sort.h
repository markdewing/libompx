
#ifndef OMPX_SORT_H
#define OMPX_SORT_H

namespace ompx {
namespace host {

template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last);

template <typename RandomAccessIterator>
void stable_sort(RandomAccessIterator first, RandomAccessIterator last);

template <typename RandomAccessIterator1, typename RandomAccessIterator2>
void sort_by_key(RandomAccessIterator1 keys_first,
                 RandomAccessIterator1 keys_last,
                 RandomAccessIterator2 values_first);

template <typename RandomAccessIterator1, typename RandomAccessIterator2>
void stable_sort_by_key(RandomAccessIterator1 keys_first,
                        RandomAccessIterator1 keys_last,
                        RandomAccessIterator2 values_first);

} // namespace host

namespace device {

template <typename RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last);

template <typename RandomAccessIterator>
void stable_sort(RandomAccessIterator first, RandomAccessIterator last);

template <typename RandomAccessIterator1, typename RandomAccessIterator2>
void sort_by_key(RandomAccessIterator1 keys_first,
                 RandomAccessIterator1 keys_last,
                 RandomAccessIterator2 values_first);

template <typename RandomAccessIterator1, typename RandomAccessIterator2>
void stable_sort_by_key(RandomAccessIterator1 keys_first,
                        RandomAccessIterator1 keys_last,
                        RandomAccessIterator2 values_first);

} // namespace device
} // namespace ompx
#endif
