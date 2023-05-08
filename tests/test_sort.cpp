
// Test of wrapper around thrust::sort

#include "ompx/sort.h"

#include <iostream>
#include <stdlib.h>

#define DTYPE int

#define N 13

void init(DTYPE *keys) {
  for (int i = 0; i < N; ++i) {
    keys[i] = rand();
  }
}

int main() {

  DTYPE keys[N];
  DTYPE *keys_begin = &keys[0];

  int NumKeys = N; // sizeof(keys) / sizeof(keys[0]);
  int errors = 0;

  init(keys);

#pragma omp target enter data map(to : keys_begin[ : NumKeys])
  { ompx::device::sort(keys_begin, keys_begin + NumKeys); }

#pragma omp target exit data map(from : keys_begin[ : NumKeys])

  for (int i = 1; i < NumKeys; i++) {
    if (keys[i] < keys[i - 1])
      errors++;
  }

  if (errors)
    std::cout << "Test FAIL" << std::endl;
  else
    std::cout << "Test PASS" << std::endl;
  return errors;
}
