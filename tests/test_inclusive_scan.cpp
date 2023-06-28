
// Test of inclusive scan

#include "ompx/inclusive_scan.h"

#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <vector>

using DTYPE = int;

void init(std::vector<DTYPE> &vec) {
  for (int i = 0; i < vec.size(); ++i) {
    vec[i] = i;
  }
}

void reference_sum(std::vector<DTYPE> &vec_in, std::vector<DTYPE> &vec_out) {
  assert(vec_in.size() == vec_out.size());

  vec_out[0] = vec_in[0];
  for (size_t i = 1; i < vec_in.size(); i++) {
    vec_out[i] = vec_in[i] + vec_out[i - 1];
  }
}

int test_separate() {

  const int N = 100;
  std::vector<DTYPE> vec(N);
  std::vector<DTYPE> ref_vec_out(N);
  std::vector<DTYPE> vec_out(N);

  init(vec);
  reference_sum(vec, ref_vec_out);

  DTYPE *vec_begin = vec.data();
  DTYPE *vec_out_begin = vec_out.data();

#pragma omp target data map(to : vec_begin[ : N])                              \
    map(from : vec_out_begin[ : N])
  ompx::device::inclusive_scan(vec_begin, vec_begin + N, vec_out_begin);

  int errors = 0;
  for (int i = 0; i < N; i++) {
    // std::cout << i << " " << ref_vec_out[i] << " " << vec_out[i] <<
    // std::endl;
    if (vec_out[i] != ref_vec_out[i])
      errors++;
  }

  return errors;
}

int test_same_vec() {

  const int N = 100;
  std::vector<DTYPE> vec(N);
  std::vector<DTYPE> ref_vec_out(N);

  init(vec);
  reference_sum(vec, ref_vec_out);

  DTYPE *vec_begin = vec.data();

#pragma omp target data map(tofrom : vec_begin[ : N])
  ompx::device::inclusive_scan(vec_begin, vec_begin + N, vec_begin);

  int errors = 0;
  for (int i = 0; i < N; i++) {
    // std::cout << i << " " << ref_vec_out[i] << " " << vec_out[i] <<
    // std::endl;
    if (vec[i] != ref_vec_out[i])
      errors++;
  }

  return errors;
}

int main() {
  int errors = test_separate();
  errors += test_same_vec();

  if (errors)
    std::cout << "Test FAIL" << std::endl;
  else
    std::cout << "Test PASS" << std::endl;
  return errors;
}
