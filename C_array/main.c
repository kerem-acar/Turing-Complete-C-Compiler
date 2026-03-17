#include "array.c"
#include <stdio.h>

int is_divisor(int k, int n) {
  if (n % k == 0) {
    return 1;
  }
  return 0;
}

IntArray *find_divisors(int n) {
  IntArray *arr = initialize_int_array(1);

  

  for (int i = 1; i < n; ++i) {
    if (is_divisor(i, n)) {
      push_back(arr, i);
    }
  }
  push_back(arr, n);
  return arr;
}



int main(void) {
  // Example usage
  
  IntArray *arr = find_divisors(30);

  for (int i = 0; i < arr->size; ++i) {
    printf("%d\n", arr->array[i]);
  }

  
  return 0;
}