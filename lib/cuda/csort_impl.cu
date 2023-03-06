
#include "thrust/sort.h"

extern "C" {

void ompx_host_sort_int(int *first, int *last) {
  thrust::sort(thrust::host, first, last);
}

void ompx_host_stable_sort_int(int *first, int *last) {
  thrust::stable_sort(thrust::host, first, last);
}

void ompx_host_sort_by_key_int_double(int *keys_first, int *keys_last,
                                      double *values_first) {
  thrust::sort_by_key(thrust::host, keys_first, keys_last, values_first);
}

void ompx_host_sort_by_key_int_int(int *keys_first, int *keys_last,
                                   int *values_first) {
  thrust::sort_by_key(thrust::host, keys_first, keys_last, values_first);
}

void ompx_host_stable_sort_by_key_int_double(int *keys_first, int *keys_last,
                                             double *values_first) {
  thrust::stable_sort_by_key(thrust::host, keys_first, keys_last, values_first);
}

void ompx_host_stable_sort_by_key_int_int(int *keys_first, int *keys_last,
                                          int *values_first) {
  thrust::stable_sort_by_key(thrust::host, keys_first, keys_last, values_first);
}

void ompx_device_sort_int(int *first, int *last) {
  thrust::sort(thrust::device, first, last);
}

void ompx_device_stable_sort_int(int *first, int *last) {
  thrust::stable_sort(thrust::device, first, last);
}

void ompx_device_sort_by_key_int_double(int *keys_first, int *keys_last,
                                        double *values_first) {
  thrust::sort_by_key(thrust::device, keys_first, keys_last, values_first);
}

void ompx_device_sort_by_key_int_int(int *keys_first, int *keys_last,
                                     int *values_first) {
  thrust::sort_by_key(thrust::device, keys_first, keys_last, values_first);
}

void ompx_device_stable_sort_by_key_int_double(int *keys_first, int *keys_last,
                                               double *values_first) {
  thrust::stable_sort_by_key(thrust::device, keys_first, keys_last,
                             values_first);
}

void ompx_device_stable_sort_by_key_int_int(int *keys_first, int *keys_last,
                                            int *values_first) {
  thrust::stable_sort_by_key(thrust::device, keys_first, keys_last,
                             values_first);
}
}
