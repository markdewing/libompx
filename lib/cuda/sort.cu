

#include <thrust/execution_policy.h>
#include <thrust/sort.h>

namespace ompx
{
    namespace host {
        template<typename RandomAccessIterator1, typename RandomAccessIterator2>
        void sort_by_key(RandomAccessIterator1 keys_first,
                         RandomAccessIterator1 keys_last,
                         RandomAccessIterator2 values_first)
        {
            thrust::sort_by_key(thrust::host, keys_first, keys_last, values_first);
        }
    }

    namespace device
    {
        template<typename RandomAccessIterator1, typename RandomAccessIterator2>
        void sort_by_key(RandomAccessIterator1 keys_first,
                         RandomAccessIterator1 keys_last,
                         RandomAccessIterator2 values_first)
        {
            thrust::sort_by_key(thrust::device, keys_first, keys_last, values_first);
        }
    }

}

// Explicit instantiations

template void ompx::device::sort_by_key(int*, int*, double*);
template void ompx::host::sort_by_key(int*, int*, double*);

