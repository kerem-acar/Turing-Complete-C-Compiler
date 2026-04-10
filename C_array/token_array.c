typedef struct {
  Token *array;
  int capacity;
  int size;
} TokenArray;

TokenArray *initialize_token_array(int capacity) {
  assert(capacity > 0);

  TokenArray *arr = malloc(sizeof(TokenArray));

  arr->array = malloc(capacity * sizeof(Token));
  arr->capacity = capacity;
  arr->size = 0;

  return arr;
}

void set_token_array_index(TokenArray *arr, int index, Token val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  assert(index >= 0 && index < arr->size);

  arr->array[index] = val;
}

void push_back_token(TokenArray *arr, Token val) {
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

void delete_token_array(TokenArray **arr) {
  assert(arr != NULL);
  assert((*arr) != NULL);
  assert((*arr)->array != NULL);

  free((*arr)->array);
  (*arr)->array = NULL;
  free((*arr));
  (*arr) = NULL;
}
