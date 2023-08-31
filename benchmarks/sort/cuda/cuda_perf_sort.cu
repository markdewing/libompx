
// Test performance of thrust::sort from CUDA

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/sort.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <string>

using TYPE = int;
// using TYPE=double;

unsigned int seed = 0;

// Initialize vector to random values
void init(std::vector<TYPE> &keys) {
  std::mt19937 rng;
  rng.seed(1);
  std::uniform_int_distribution<int> uniform_int_dist;
  for (int i = 0; i < keys.size(); ++i) {
    keys[i] = (TYPE)uniform_int_dist(rng);
  }
}

double run_n(int N) {
  std::vector<TYPE> host_keys(N);

  int NumKeys = N; // sizeof(keys) / sizeof(keys[0]);
  int errors = 0;

  init(host_keys);

  auto start = std::chrono::steady_clock::now();

  thrust::device_vector<TYPE> keys(host_keys);
  thrust::sort(keys.begin(), keys.end());

  thrust::copy(keys.begin(), keys.end(), host_keys.begin());

  auto end = std::chrono::steady_clock::now();

  std::chrono::duration<double> elapsed = end - start;

  for (int i = 1; i < NumKeys; i++) {
    if (host_keys[i] < host_keys[i - 1])
      errors++;
  }

  if (errors)
    std::cout << "Test FAIL" << std::endl;

  return elapsed.count();
}

void warmup() {
  const int warmup_N = 10;
  std::vector<TYPE> host_keys(warmup_N);
  init(host_keys);
  thrust::device_vector<TYPE> keys(warmup_N);
  thrust::sort(keys.begin(), keys.end());
}

void print_header() {
  std::cout << "# Sort test using CUDA and Thrust" << std::endl;
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
      N = std::stoi(argv[++i]);
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
