int *start_experiment(int size) {
  int *arr = malloc(size * sizeof(int));

  for (int i = 0; i < size; ++i) {
    arr[i] = -1;
  }

  return arr;
}

int push_key(int val, int *arr, int size) {
  int index = val % size;
  int start_index = index;

  if (arr[index] == -1) {
    arr[index] = val;
    return 0;
  }

  int probes = 0;

  while (arr[index] != -1) {
    index++;
    probes++;

    if (index == size) {
      index = 0;
    }

    if (index == start_index) {
      assert(0);
    }
  }

  arr[index] = val;
  

  return probes;
}

void run_test_case(int size, double loading) {
  srand(1);
  
  int *arr = start_experiment(size);
  
  int total_probes = 0;

  int items_to_insert = (int)(size * loading);

  for (int i = 0; i < items_to_insert; i++) {
    int val = rand();
    total_probes += push_key(val, arr, size);
  }

  printf("%d\n", total_probes);

  free(arr);
}