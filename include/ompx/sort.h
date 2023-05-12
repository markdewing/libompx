#ifndef OMPX_SORT_H
#define OMPX_SORT_H

#include <omp.h>
#include <stddef.h>

namespace ompx {
namespace host {

template <typename T>
void ompx_sort(T* first, size_t NumElements);

template <typename T>
void sort(T* first, T* last) {
  size_t NumElements = last - first;
  ompx::host::ompx_sort(first, NumElements);
}
} // namespace host

namespace device {
template <typename T>
void ompx_sort(T* first, size_t NumElements);

template <typename T>
void sort(T* first, T* last) {
  size_t NumElements = last - first;
  int dev = omp_get_default_device();
  int present = omp_target_is_present(first, dev);
  if (present) {
#pragma omp target data use_device_ptr(first)
    ompx::device::ompx_sort(first, NumElements);
  } else {
#pragma omp target data map(tofrom : first[ : NumElements])                    \
    use_device_ptr(first)
    ompx::device::ompx_sort(first, NumElements);
  }
}
} // namespace device
} // namespace ompx

#endif
