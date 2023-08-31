
// Test performance of sort

#include "ompx/sort.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <string>

// using TYPE=int;
using TYPE = double;

unsigned int seed = 0;

// Initial vector to random values
void init(std::vector<TYPE> &keys) {
  std::mt19937 rng;
  rng.seed(1);
  std::uniform_int_distribution<int> uniform_int_dist;
  for (int i = 0; i < keys.size(); ++i) {
    keys[i] = (TYPE)uniform_int_dist(rng);
  }
}

double run_n(int N) {
  std::vector<TYPE> keys(N);
  TYPE *keys_begin = keys.data();

  int NumKeys = N; // sizeof(keys) / sizeof(keys[0]);
  int errors = 0;

  init(keys);

  auto start = std::chrono::steady_clock::now();

#pragma omp target enter data map(to : keys_begin[ : NumKeys])
  { ompx::device::sort(keys_begin, keys_begin + NumKeys); }
#pragma omp target exit data map(from : keys_begin[ : NumKeys])

  auto end = std::chrono::steady_clock::now();

  std::chrono::duration<double> elapsed = end - start;
  // std::cout << "N = " << N << " Time = " << elapsed.count() << std::endl;

  for (int i = 1; i < NumKeys; i++) {
    if (keys[i] < keys[i - 1])
      errors++;
  }

  if (errors)
    std::cout << "Test FAIL" << std::endl;
  // else
  //   std::cout << "Test PASS" << std::endl;
  return elapsed.count();
}

void warmup() {
  const int warmup_N = 10;
  std::vector<TYPE> keys(warmup_N);
  init(keys);
  TYPE *keys_begin = keys.data();
#pragma omp target enter data map(to : keys_begin[ : warmup_N])
  { ompx::device::sort(keys_begin, keys_begin + warmup_N); }

#pragma omp target exit data map(from : keys_begin[ : warmup_N])
}

void print_header() {
  std::cout << "# Sort test using libompx" << std::endl;
  std::cout << "# type = " << typeid(TYPE).name()
            << " size of type = " << sizeof(TYPE) << std::endl;
  std::cout << "# seed = " << seed << std::endl;
  std::cout << "# N (bytes)  Average time" << std::endl;
}

int main(int argc, char **argv) {
  size_t N = 100;
  int nloop = 20;
  bool do_print_header = true;
  for (int i = 1; i < argc; i++) {
    std::string arg(argv[i]);

    // Length of array to sort
    if (arg == "-n") {
      std::string val(argv[++i]);
      N = std::stoi(val);
    }

    // Number of loops (number of times to run the sort)
    if (arg == "-l") {
      nloop = std::stoi(argv[++i]);
    }

    if (arg == "--no-header") {
      do_print_header = false;
    }

    if (arg == "--only-print-header") {
      print_header();
      return 0;
    }

    if (arg == "--seed") {
      seed = std::stoi(argv[++i]);
    }
  }

  if (seed == 0) {
    std::random_device rd;
    seed = rd();
  }

  warmup();
  double total = 0.0;
  for (int i = 0; i < nloop; i++) {
    total += run_n(N);
  }

  uint64_t bytes = N * sizeof(TYPE);

  if (do_print_header)
    print_header();
  std::cout << bytes << " " << total / nloop << std::endl;
}
