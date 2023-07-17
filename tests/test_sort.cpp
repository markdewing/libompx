
// Test of wrapper around thrust::sort

#include "ompx/sort.h"

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <iostream>
#include <stdlib.h>
#include <vector>

template <typename T> void init(std::vector<T> &keys) {
  for (int i = 0; i < keys.size(); ++i) {
    keys[i] = (T)rand();
  }
}

TEMPLATE_TEST_CASE("sort_by_key", "[sort]", int, float, double) {

  int N = GENERATE(0, 1, 2, 3, 4, 8, 13);
  std::cout << "size = " << N << std::endl;
  std::vector<TestType> keys(N);
  TestType *keys_begin = keys.data();

  int errors = 0;

  init(keys);

#pragma omp target enter data map(to : keys_begin[ : N])
  { ompx::device::sort(keys_begin, keys_begin + N); }

#pragma omp target exit data map(from : keys_begin[ : N])

  if (false)
    for (int i = 0; i < N; i++) {
      std::cout << i << " " << keys[i] << std::endl;
    }

  for (int i = 1; i < N; i++) {
    REQUIRE(keys[i - 1] < keys[i]);
  }
}
