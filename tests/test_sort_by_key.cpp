
// Test of sort_by_key

#include "ompx/sort_by_key.h"
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>


#include <vector>
#include <iostream>
#include <stdlib.h>

template<typename K, typename V>
void init(std::vector<K>& keys, std::vector<V>& values) {
  for (int i = 0; i < keys.size(); ++i) {
    keys[i] = (K)rand();
    values[i] = (V)keys[i];
  }
}

// Can't get this to work
//TEMPLATE_PRODUCT_TEST_CASE("sort", "[sort]", (int, float), (int, float, double)) {

TEMPLATE_TEST_CASE("sort_by_key", "[sort]", int, float, double) {

  size_t N = GENERATE(0, 1, 2, 3, 4, 8, 13);
  //using K = TestType::get<0>();
  //using V = TestType::get<1>();
  using K = int;
  using V = TestType; 
  std::vector<K> keys(N);
  K *keys_begin = keys.data();

  std::vector<V> values_vec(N);
  V *values = values_vec.data();

  int errors = 0;

  init(keys, values_vec);

#pragma omp target enter data map(to : keys_begin[ : N])                 \
    map(to : values[ : N])
  { ompx::device::sort_by_key(keys_begin, keys_begin + N, values); }
#pragma omp target exit data map(from : keys_begin[ : N])                \
    map(from : values[ : N])

  for (int i = 1; i < N; i++) {
    REQUIRE(keys[i] >= keys[i - 1]);
    REQUIRE(values[i - 1] >= values[i - 1]);
  }

}
