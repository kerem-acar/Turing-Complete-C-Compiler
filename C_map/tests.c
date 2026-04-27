#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "../C_map/hash.c"

int main() {
  int size1 = 211;
  int size2 = 307;
  int size3 = 401;
  
  //As the size increases the total number of probes increases
  run_test_case(size1, 0.6);
  run_test_case(size2, 0.6);
  run_test_case(size3, 0.6);

  run_test_case(size1, 0.5);
  run_test_case(size2, 0.5);
  run_test_case(size3, 0.5);

  run_test_case(size1, 0.4);
  run_test_case(size2, 0.4);
  run_test_case(size3, 0.4);
  
  run_test_case(size1, 0.3);
  run_test_case(size2, 0.3);
  run_test_case(size3, 0.3);

  
  run_test_case(size1, 0.2);
  run_test_case(size2, 0.2);
  run_test_case(size3, 0.2);
  return 0;
}