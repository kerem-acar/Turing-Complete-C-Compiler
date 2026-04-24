#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "../C_map/hash.c"

int main() {
  int size1 = 211;
  int size2 = 307;
  int size3 = 401;

  run_test_case(size1, 0.3);
  run_test_case(size2, 0.4);
  run_test_case(size3, 0.5);

  return 0;
}