typedef struct {
  AST_BlockItem *array;
  int capacity;
  int size;
} BlockArray;

BlockArray *initialize_block_array(int capacity) {
  assert(capacity > 0);

  BlockArray *arr = malloc(sizeof(BlockArray));

  arr->array = malloc(capacity * sizeof(AST_BlockItem));
  arr->capacity = capacity;
  arr->size = 0;

  return arr;
}

void set_block_array_index(BlockArray *arr, int index, AST_BlockItem val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  assert(index >= 0 && index < arr->size);

  arr->array[index] = val;
}

void push_back_block(BlockArray *arr, AST_BlockItem val) {
  assert(arr != NULL);
  assert(arr->array != NULL);
  if (arr->size == arr->capacity) {
    AST_BlockItem *tmp = malloc((arr->capacity * 2) * sizeof(AST_BlockItem));

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

void delete_block_array(BlockArray **arr) {
  assert(arr != NULL);
  assert((*arr) != NULL);
  assert((*arr)->array != NULL);

  free((*arr)->array);
  (*arr)->array = NULL;
  free((*arr));
  (*arr) = NULL;
}