#ifndef OMPX_SORT_BY_KEY_H
#define OMPX_SORT_BY_KEY_H

#include <omp.h>
#include <stddef.h>
#ifdef ONEAPI
#include <oneapi/dpl/algorithm>
#include <oneapi/dpl/execution>
#endif

namespace ompx {

//
// Device library
//

namespace device {

#ifdef ONEAPI
template <typename T1, typename T2> class _sort_helper {
public:
  T1 key;
  T2 value;

  bool operator<(const _sort_helper &o) const { return key < o.key; }
};

template <typename T1, typename T2>
void sort_by_key(T1 *key_begin, T1 *key_end, T2 *value_begin) {
  size_t NumElements = key_end - key_begin;
  int dev = omp_get_default_device();

  using sort_helper = _sort_helper<T1, T2>;
  sort_helper *sh =
      (sort_helper *)omp_target_alloc(NumElements * sizeof(sort_helper), dev);
#pragma omp target parallel for is_device_ptr(sh)
  for (size_t i = 0; i < NumElements; i++) {
    sh[i].key = key_begin[i];
    sh[i].value = value_begin[i];
  }

  std::sort(oneapi::dpl::execution::dpcpp_default, sh, sh + NumElements);

#pragma omp target parallel for is_device_ptr(sh)
  for (size_t i = 0; i < NumElements; i++) {
    key_begin[i] = sh[i].key;
    value_begin[i] = sh[i].value;
  }
}

#else

template <typename T1, typename T2>
void ompx_sort_by_key(T1 *B, size_t NumElements, T2 *V);

template <typename T1, typename T2>
void sort_by_key(T1 *B, size_t NumElements, T2 *V) {
#pragma omp target data use_device_ptr(B, V)
  ompx_sort_by_key(B, NumElements, V);
  // ompx_sort_by_key_impl((void *)B, NumElements, sizeof(T1), (void *)V,
  // sizeof(T2));
}

template <typename T1, typename T2> void sort_by_key(T1 *B, T1 *E, T2 *V) {
  sort_by_key(B, E - B, V);
}

#endif

} // namespace device
} // namespace ompx

#endif
