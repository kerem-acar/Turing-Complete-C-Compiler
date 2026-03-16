#include <stdlib.h>
#include <assert.h>

typedef struct {
  int *array;
  int capacity;
} IntArray;

IntArray *initialize_int_array(int capacity) {
  IntArray *arr = malloc(sizeof(IntArray));
  
  assert(capacity > 0);

  arr->array = malloc(capacity * sizeof(int));
  arr->capacity = capacity;

  return arr;
}

void set_array_index(IntArray *arr, int index, int val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  assert(index >= 0 && index < arr->capacity);

  arr->array[index] = val;
  
}

void push_back(IntArray *arr, int val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  int *tmp = malloc((arr->capacity * 2) * sizeof(int));

  for (int i = 0; i < arr->capacity; ++i) {
    tmp[i] = arr->array[i];
  }

  tmp[arr->capacity] = val;

  free(arr->array);

  arr->array = tmp;
  arr->capacity *= 2;

  tmp = NULL;
}

void delete_array(IntArray **arr) {
  assert((*arr) != NULL);
  assert((*arr)->array != NULL);

  free((*arr)->array);
  (*arr)->array = NULL;
  free((*arr));
  (*arr) = NULL;
}
