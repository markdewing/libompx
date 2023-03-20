
#include <cassert>
#include <ompx/sort.h>

int main() {
  const int nkey = 4;
  double values[4] = {1.0, 3.0, 4.0, 2.0};

  double sorted_values[4] = {1.0, 2.0, 3.0, 4.0};

#if 0
  ompx::host::ompx_sort(values, values + 4);

  for (int i = 0; i < nkey; i++) {
    assert(values[i] == sorted_values[i]);
  }
#endif

  double host_values[4] = {1.0, 3.0, 4.0, 2.0};
  double *values_ptr = host_values;

#pragma omp target data map(tofrom: values_ptr[:4])
  ompx::device::ompx_sort(values_ptr, 4);

  for (int i = 0; i < nkey; i++) {
    assert(host_values[i] == sorted_values[i]);
  }

  return 0;
}

