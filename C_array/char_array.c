#include <assert.h>
#include <stdlib.h>
#pragma once

typedef struct {
  char *array;
  int capacity;
  int size;
} CharArray;

CharArray *initialize_char_array(int capacity) {
  assert(capacity > 0);

  CharArray *arr = malloc(sizeof(CharArray));

  arr->array = malloc(capacity * sizeof(char));
  arr->capacity = capacity;
  arr->size = 0;

  return arr;
}

void set_char_array_index(CharArray *arr, int index, char val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  assert(index >= 0 && index < arr->size);

  arr->array[index] = val;
}

void push_back_char(CharArray *arr, char val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  if (arr->size == arr->capacity) {
    char *tmp = malloc((arr->capacity * 2) * sizeof(char));

    for (int i = 0; i < arr->capacity; ++i) {
      tmp[i] = arr->array[i];
    }

    tmp[arr->capacity] = val;

    free(arr->array);

    arr->array = tmp;
    arr->capacity *= 2;
    arr->size++;
    tmp = NULL;
  } else {
    arr->array[arr->size] = val;
    arr->size++;
  }
}

void delete_char_array(CharArray **arr) {
  assert(arr != NULL);
  assert((*arr) != NULL);
  assert((*arr)->array != NULL);

  free((*arr)->array);
  (*arr)->array = NULL;
  free((*arr));
  (*arr) = NULL;
}
