
// Test of host sort

#include "ompx/sort.h"

#include <iostream>
#include <stdlib.h>

#define DTYPE int

#define N 13

class Cmp {
public:
  bool operator()(DTYPE a, DTYPE b) const {
    // reverse it for fun
    return a > b;
  }
};

bool cmp(void *a, void *b) {
  Cmp c;
  return c(*(DTYPE *)a, *(DTYPE *)b);
}


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

  ompx::host::sort(keys_begin, keys_begin + NumKeys, cmp);

  for (int i = 1; i < NumKeys; i++) {
    if (keys[i] > keys[i - 1])
      errors++;
  }

  if (errors)
    std::cout << "Test FAIL" << std::endl;
  else
    std::cout << "Test PASS" << std::endl;
  return errors;
}
