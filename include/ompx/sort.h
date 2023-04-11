#ifndef OMPX_SORT_H
#define OMPX_SORT_H

#include <functional>

namespace ompx {

typedef bool (*ompx_sort_cmp_ty)(void *, void *);

template <typename T> class __Cmp {
public:
  bool operator()(T a, T b) const { return a < b; }
};

template <typename T> bool __cmp(void *a, void *b) {
  __Cmp<T> c;
  return c(*(T *)a, *(T *)b);
}

namespace host {
void ompx_sort_impl(void *B, void *E, uint32_t size, ompx_sort_cmp_ty F);

template <typename T>
void ompx_sort(T *B, uint32_t NumElements, ompx_sort_cmp_ty Cmp) {
  ompx_sort_impl((void *)B, (void *)(B + NumElements), sizeof(T), Cmp);
}

template <typename T> void ompx_sort(T *B, uint32_t NumElements) {
  ompx_sort_impl((void *)B, (void *)(B + NumElements), sizeof(T), __cmp<T>);
}

template <typename T> void ompx_sort(T *B, T *E) { ompx_sort(B, E - B); }

template <typename T> void ompx_sort(T *B, T *E, ompx_sort_cmp_ty Cmp) {
  ompx_sort(B, E - B, Cmp);
}

} // namespace host

namespace device {

void ompx_sort_impl(void *B, void *E, uint32_t size, ompx_sort_cmp_ty F);
template <typename T>
void ompx_sort(T *B, int NumElements, ompx_sort_cmp_ty Cmp) {
#pragma omp target data use_device_ptr(B)
  ompx_sort_impl((void *)B, (void *)(B + NumElements), sizeof(T), Cmp);
}

template <typename T> void ompx_sort(T *B, T *E, ompx_sort_cmp_ty Cmp) {
  ompx_sort(B, E - B, Cmp);
}

#pragma omp begin declare target
template <typename T> class __Cmp {
public:
  bool operator()(T a, T b) const { return a < b; }
};

template <typename T> bool __cmp(void *a, void *b) {
  __Cmp<T> c;
  return c(*(T *)a, *(T *)b);
}
#pragma omp end declare target

template <typename T> void ompx_sort(T *B, uint32_t NumElements) {
  ompx_sort_cmp_ty dev_fptr = nullptr;

#pragma omp target map(from : dev_fptr)
  dev_fptr = &__cmp<T>;

#pragma omp target data use_device_ptr(B)
  ompx_sort_impl((void *)B, (void *)(B + NumElements), sizeof(T), dev_fptr);
}

template <typename T> void ompx_sort(T *B, T *E) { ompx_sort(B, E - B); }


// sort_by_key
void ompx_sort_by_key_impl(void *B, void *E, uint32_t sizeK, void *K, uint32_t sizeV, ompx_sort_cmp_ty F);

template <typename T1, typename T2>
void sort_by_key(T1 *B, uint32_t NumElements, T2 *V, ompx_sort_cmp_ty Cmp) {
#pragma omp target data use_device_ptr(B,V)
    ompx_sort_by_key_impl((void *)B, (void *)(B + NumElements), sizeof(T1), (void *)V, sizeof(T2), Cmp);
}

template <typename T1, typename T2>
void sort_by_key(T1 *B, uint32_t NumElements, T2 *V) {
  ompx_sort_cmp_ty dev_fptr = nullptr;

#pragma omp target map(from : dev_fptr)
  dev_fptr = &__cmp<T1>;

#pragma omp target data use_device_ptr(B,V)
  ompx_sort_by_key_impl((void *)B, (void *)(B + NumElements), sizeof(T1), (void *)V, sizeof(T2), dev_fptr);
}

template <typename T1, typename T2> void sort_by_key(T1 *B, T1 *E, T2 *V, ompx_sort_cmp_ty Cmp) {
  sort_by_key(B, E - B, V, Cmp);
}

template <typename T1, typename T2> void sort_by_key(T1 *B, T1 *E, T2 *V) {
  sort_by_key(B, E - B, V);
}




} // namespace device

} // namespace ompx
#endif
