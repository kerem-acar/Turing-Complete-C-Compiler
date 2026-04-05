#include <assert.h>
#include <stdlib.h>
#pragma once

typedef struct {
  %TYPE% *array;
  int capacity;
  int size;
} %PREFIX%Array;

%PREFIX%Array *initialize_%NAME%_array(int capacity) {
  assert(capacity > 0);
  
  %PREFIX%Array *arr = malloc(sizeof(%PREFIX%Array));


  arr->array = malloc(capacity * sizeof(%TYPE%));
  arr->capacity = capacity;
  arr->size = 0;

  return arr;
}

void set_%NAME%_array_index(%PREFIX%Array *arr, int index, %TYPE% val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  assert(index >= 0 && index < arr->size);

  arr->array[index] = val;
}

void push_back_%NAME%(%PREFIX%Array *arr, %TYPE% val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  if (arr->size == arr->capacity) {
    %TYPE% *tmp = malloc((arr->capacity * 2) * sizeof(%TYPE%));

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

void delete_%NAME%_array(%PREFIX%Array **arr) {
  assert(arr != NULL);
  assert((*arr) != NULL);
  assert((*arr)->array != NULL);

  free((*arr)->array);
  (*arr)->array = NULL;
  free((*arr));
  (*arr) = NULL;
}