#include "../lexer/token.c"
#include <assert.h>
#include <stdlib.h>
#pragma once

typedef struct {
  Token *array;
  int capacity;
  int size;
} TokenArray;

TokenArray *initialize_token_array(int capacity) {
  TokenArray *arr = malloc(sizeof(TokenArray));

  assert(capacity > 0);

  arr->array = malloc(capacity * sizeof(Token));
  arr->capacity = capacity;
  arr->size = 0;

  return arr;
}

void set_array_index(TokenArray *arr, int index, Token val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  assert(index >= 0 && index < arr->capacity);

  arr->array[index] = val;
  arr->size++;
}

void push_back(TokenArray *arr, Token val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  if (arr->size == arr->capacity) {
    Token *tmp = malloc((arr->capacity * 2) * sizeof(Token));

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

void delete_array(TokenArray **arr) {
  assert((*arr) != NULL);
  assert((*arr)->array != NULL);

  free((*arr)->array);
  (*arr)->array = NULL;
  free((*arr));
  (*arr) = NULL;
}
