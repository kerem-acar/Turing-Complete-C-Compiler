typedef struct {
  AST_Statement *array;
  int capacity;
  int size;
} StatArray;

StatArray *initialize_stat_array(int capacity) {
  assert(capacity > 0);

  StatArray *arr = malloc(sizeof(StatArray));

  arr->array = malloc(capacity * sizeof(AST_Statement));
  arr->capacity = capacity;
  arr->size = 0;

  return arr;
}

void set_stat_array_index(StatArray *arr, int index, AST_Statement val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  assert(index >= 0 && index < arr->size);

  arr->array[index] = val;
}

void push_back_stat(StatArray *arr, AST_Statement val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  if (arr->size == arr->capacity) {
    AST_Statement *tmp = malloc((arr->capacity * 2) * sizeof(AST_Statement));

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

void delete_stat_array(StatArray **arr) {
  assert(arr != NULL);
  assert((*arr) != NULL);
  assert((*arr)->array != NULL);

  free((*arr)->array);
  (*arr)->array = NULL;
  free((*arr));
  (*arr) = NULL;
}