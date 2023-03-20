#ifndef OMPX_SORT_H
#define OMPX_SORT_H

#include <functional>

namespace ompx {

namespace host {

} // namespace host

namespace device {

typedef bool (*ompx_sort_cmp_ty)(void *, void *);
void ompx_sort_impl(void *B, void *E, int size, ompx_sort_cmp_ty F);

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
  bool operator()(T a, T b) const {
    return a < b;
  }
};

template <typename T>
bool __cmp(void *a, void *b) {
  __Cmp<T> c;
  return c(*(T *)a, *(T *)b);
}
#pragma omp end declare target

template <typename T>
void ompx_sort(T *B, int NumElements) {
   ompx_sort_cmp_ty dev_fptr = nullptr;

#pragma omp target map(from : dev_fptr)
     dev_fptr = &__cmp<T>;

#pragma omp target data use_device_ptr(B)
     ompx_sort_impl((void *)B, (void *)(B + NumElements), sizeof(T), dev_fptr);
}

template <typename T> void ompx_sort(T *B, T *E) {
  ompx_sort(B, E - B);
}

} // namespace device

}
#endif

