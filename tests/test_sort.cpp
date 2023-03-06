
#include <cassert>
#include <ompx/sort.h>

int main() {
  const int nkey = 4;
  int keys[4] = {1, 3, 4, 2};
  double values[4] = {1.0, 3.0, 4.0, 2.0};

  int sorted_keys[4] = {1, 2, 3, 4};
  double sorted_values[4] = {1.0, 2.0, 3.0, 4.0};

  ompx::host::sort_by_key(keys, keys + 4, values);

  for (int i = 0; i < nkey; i++) {
    assert(keys[i] == sorted_keys[i]);
    assert(values[i] == sorted_values[i]);
  }

  int host_keys[4] = {1, 3, 4, 2};
  double host_values[4] = {1.0, 3.0, 4.0, 2.0};
  int *keys_ptr = host_keys;
  double *values_ptr = host_values;

#pragma omp target data map(tofrom: keys_ptr[:4], values_ptr[:4]) \
                        use_device_ptr(keys_ptr, values_ptr)
  ompx::device::sort_by_key(keys_ptr, keys_ptr + 4, values_ptr);

  for (int i = 0; i < nkey; i++) {
    assert(host_keys[i] == sorted_keys[i]);
    assert(host_values[i] == sorted_values[i]);
  }

  return 0;
}
