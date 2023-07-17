
// Test of inclusive scan

#include "ompx/inclusive_scan.h"

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <vector>

template<typename T>
void init(std::vector<T> &vec) {
  for (int i = 0; i < vec.size(); ++i) {
    vec[i] = (T)i;
  }
}

template<typename T>
void reference_sum(std::vector<T> &vec_in, std::vector<T> &vec_out) {
  assert(vec_in.size() == vec_out.size());

  if (vec_in.size() == 0) return;

  vec_out[0] = vec_in[0];
  for (size_t i = 1; i < vec_in.size(); i++) {
    vec_out[i] = vec_in[i] + vec_out[i - 1];
  }
}

TEMPLATE_TEST_CASE("inclusive_scan_separate","[scan]",int,float,double) {

  size_t N = GENERATE(0,1,2,100);
  std::vector<TestType> vec(N);
  std::vector<TestType> ref_vec_out(N);
  std::vector<TestType> vec_out(N);

  init(vec);
  reference_sum(vec, ref_vec_out);

  auto *vec_begin = vec.data();
  auto *vec_out_begin = vec_out.data();

#pragma omp target data map(to : vec_begin[ : N])                              \
    map(from : vec_out_begin[ : N])
  ompx::device::inclusive_scan(vec_begin, vec_begin + N, vec_out_begin);

  for (int i = 0; i < N; i++) {
    // std::cout << i << " " << ref_vec_out[i] << " " << vec_out[i] <<
    // std::endl;
    REQUIRE(vec_out[i] == ref_vec_out[i]);
  }
}

TEMPLATE_TEST_CASE("inclusive_scan_same","[scan]",int,float,double) {

  size_t N = GENERATE(0,1,2,100);
  std::vector<TestType> vec(N);
  std::vector<TestType> ref_vec_out(N);

  init(vec);
  reference_sum(vec, ref_vec_out);

  auto *vec_begin = vec.data();

#pragma omp target data map(tofrom : vec_begin[ : N])
  ompx::device::inclusive_scan(vec_begin, vec_begin + N, vec_begin);

  for (int i = 0; i < N; i++) {
    // std::cout << i << " " << ref_vec_out[i] << " " << vec_out[i] <<
    // std::endl;
    REQUIRE(vec[i] == ref_vec_out[i]);
  }

}

