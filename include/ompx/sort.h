#ifndef OMPX_SORT_H
#define OMPX_SORT_H

namespace ompx {
namespace host {
template <typename RandomAccessIterator1, typename RandomAccessIterator2>
void sort_by_key(RandomAccessIterator1 keys_first,
                 RandomAccessIterator1 keys_last,
                 RandomAccessIterator2 values_first);
}

namespace device {
template <typename RandomAccessIterator1, typename RandomAccessIterator2>
void sort_by_key(RandomAccessIterator1 keys_first,
                 RandomAccessIterator1 keys_last,
                 RandomAccessIterator2 values_first);
}

} // namespace ompx

#endif
