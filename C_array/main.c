#include "array.c"

int main() {
  // Example usage
  IntArray *arr = initialize_int_array(3);

  set_array_index(arr, 0, 5);
  set_array_index(arr, 1, 2);
  set_array_index(arr, 2, 9);

  push_back(arr, 11);

  delete_array(&arr);

  return 0;
}