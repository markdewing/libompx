
// Test of sort_by_key

#include "ompx/sort_by_key.h"

#include <iostream>
#include <stdlib.h>

using DTYPE = int;
using VTYPE = int;

#define N 13

void init(DTYPE *keys, VTYPE *values) {
  for (int i = 0; i < N; ++i) {
    keys[i] = rand();
    values[i] = (VTYPE)keys[i];
  }
}

int main() {

  DTYPE keys[N];
  DTYPE *keys_begin = &keys[0];

  VTYPE values[N];
  int NumKeys = N; // sizeof(keys) / sizeof(keys[0]);

  int errors = 0;

  init(keys, values);

#pragma omp target enter data map(to : keys_begin[ : NumKeys])                 \
    map(to : values[ : NumKeys])
  { ompx::device::sort_by_key(keys_begin, keys_begin + NumKeys, values); }
#pragma omp target exit data map(from : keys_begin[ : NumKeys])                \
    map(from : values[ : NumKeys])

  for (int i = 1; i < NumKeys; i++) {
    if (keys[i] < keys[i - 1] || values[i - 1] < values[i - 1])
      errors++;
    // std::cout << i << " " << keys[i] << "  " << values[i] << std::endl;
  }

  if (errors)
    std::cout << "Test FAIL" << std::endl;
  else
    std::cout << "Test PASS" << std::endl;
  return errors;
}
