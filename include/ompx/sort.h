#ifndef OMPX_SORT_H
#define OMPX_SORT_H

#include <omp.h>
#include <stddef.h>
#include "sort_types.h"
#ifdef ONEAPI
#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>
#endif

namespace ompx {

//
// Host library
//

namespace host {

template <typename T> void ompx_sort(T *first, size_t NumElements);

void ompx_sort_cmp(void *first, size_t NumElements, size_t elementSize,
                   ompx_sort_cmp_ty Cmp);

template <typename T> void sort(T *first, T *last) {
  size_t NumElements = last - first;
  ompx::host::ompx_sort(first, NumElements);
}

template <typename T> void sort(T *first, T *last, ompx_sort_cmp_ty Cmp) {
  size_t NumElements = last - first;
  ompx::host::ompx_sort_cmp(first, NumElements, sizeof(T), Cmp);
}
} // namespace host

//
// Device library
//

namespace device {
#ifdef ONEAPI
template <typename T> void sort(T *first, T *last) {
  size_t NumElements = last - first;
  int dev = omp_get_default_device();
  int present = omp_target_is_present(first, dev);
  if (present) {
#pragma omp target data use_device_ptr(first)
    std::sort(oneapi::dpl::execution::dpcpp_default, first,
              first + NumElements);
  } else {
#pragma omp target data map(tofrom : first[ : NumElements])                    \
    use_device_ptr(first)
    std::sort(oneapi::dpl::execution::dpcpp_default, first,
              first + NumElements);
  }
}

template <typename T, typename Cmp> void sort(T *first, T *last, Cmp F) {
  size_t NumElements = last - first;
  int dev = omp_get_default_device();
  int present = omp_target_is_present(first, dev);
  if (present) {
#pragma omp target data use_device_ptr(first)
    std::sort(oneapi::dpl::execution::dpcpp_default, first, first + NumElements,
              F);
  } else {
#pragma omp target data map(tofrom : first[ : NumElements])                    \
    use_device_ptr(first)
    std::sort(oneapi::dpl::execution::dpcpp_default, first, first + NumElements,
              F);
  }
}

#else
template <typename T> void ompx_sort(T *first, size_t NumElements);

void ompx_sort_cmp(void *first, size_t NumElements, size_t elementSize,
                   ompx_sort_cmp_ty Cmp);

template <typename T> void sort(T *first, T *last) {
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

template <typename T, typename Cmp> bool cmp_wrapper(void *a, void *b) {
  Cmp c;
  return c(*(T *)a, *(T *)b);
}

template <typename T, typename Cmp> void sort(T *first, T *last, Cmp F) {

  ompx_sort_cmp_ty dev_fptr;
#pragma omp target map(from : dev_fptr)
  { dev_fptr = &cmp_wrapper<T, Cmp>; }

  size_t NumElements = last - first;
  int dev = omp_get_default_device();
  int present = omp_target_is_present(first, dev);
  if (present) {
#pragma omp target data use_device_ptr(first)
    ompx::device::ompx_sort_cmp(first, NumElements, sizeof(T), dev_fptr);
  } else {
#pragma omp target data map(tofrom : first[ : NumElements])                    \
    use_device_ptr(first)
    ompx::device::ompx_sort_cmp(first, NumElements, sizeof(T), dev_fptr);
  }
}

#endif

} // namespace device
} // namespace ompx

#endif
