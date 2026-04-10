typedef struct {
  int *array;
  int capacity;
  int size;
} IntArray;

IntArray *initialize_int_array(int capacity) {
  assert(capacity > 0);

  IntArray *arr = malloc(sizeof(IntArray));

  arr->array = malloc(capacity * sizeof(int));
  arr->capacity = capacity;
  arr->size = 0;

  return arr;
}

void set_int_array_index(IntArray *arr, int index, int val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  assert(index >= 0 && index < arr->size);

  arr->array[index] = val;
}

void push_back_int(IntArray *arr, int val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  if (arr->size == arr->capacity) {
    int *tmp = malloc((arr->capacity * 2) * sizeof(int));

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

void delete_int_array(IntArray **arr) {
  assert(arr != NULL);
  assert((*arr) != NULL);
  assert((*arr)->array != NULL);

  free((*arr)->array);
  (*arr)->array = NULL;
  free((*arr));
  (*arr) = NULL;
}
