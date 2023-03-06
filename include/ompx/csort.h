
#ifndef OMPX_CSORT_H
#define OMPX_CSORT_H

#ifdef __cplusplus
extern "C" {
#endif

void ompx_host_sort_int(int *first, int *last);

void ompx_host_stable_sort_int(int *first, int *last);

void ompx_host_sort_by_key_int_double(int *keys_first, int *keys_last,
                                      double *values_first);

void ompx_host_sort_by_key_int_int(int *keys_first, int *keys_last,
                                   int *values_first);

void ompx_host_stable_sort_by_key_int_double(int *keys_first, int *keys_last,
                                             double *values_first);

void ompx_host_stable_sort_by_key_int_int(int *keys_first, int *keys_last,
                                          int *values_first);

void ompx_device_sort_int(int *first, int *last);

void ompx_device_stable_sort_int(int *first, int *last);

void ompx_device_sort_by_key_int_double(int *keys_first, int *keys_last,
                                        double *values_first);

void ompx_device_sort_by_key_int_int(int *keys_first, int *keys_last,
                                     int *values_first);

void ompx_device_stable_sort_by_key_int_double(int *keys_first, int *keys_last,
                                               double *values_first);

void ompx_device_stable_sort_by_key_int_int(int *keys_first, int *keys_last,
                                            int *values_first);

#ifdef __cplusplus
}
#endif

#endif
