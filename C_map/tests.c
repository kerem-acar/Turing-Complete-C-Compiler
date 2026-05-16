#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "../C_map/hash.c"
#include "../C_map/map.c"

int main() {
  StackIndexMap m;
  map_init(&m, 4);

  assert(m.capacity == 4);
  assert(!m.size);
  assert(m.data != NULL);

  map_insert(&m, strdup("apple"), 10);
  map_insert(&m, strdup("banana"), 20);

  assert(m.size == 2);

  FindRes res = map_lookup(&m, "apple");

  assert(res.found);
  assert(res.val == 10);

  res = map_lookup(&m, "banana");

  assert(res.found);
  assert(res.val == 20);

  res = map_lookup(&m, "orange");
  assert(!res.found);

  map_insert(&m, "apple", 30);

  assert(m.size == 2);

  res = map_lookup(&m, "apple");

  assert(res.found);
  assert(res.val == 30);

  delete_key(&m, "apple");

  assert(m.size);

  res = map_lookup(&m, "apple");

  assert(!res.found);

  res = map_lookup(&m, "banana");

  assert(res.found);
  assert(res.val == 20);

  map_insert(&m, strdup("apple"), 40);

  res = map_lookup(&m, "apple");
  
  assert(res.found);
  assert(res.val == 40);
  assert(m.size == 2);

  map_insert(&m, strdup("orange"), 50);
  map_insert(&m, strdup("pineapple"), 60);

  assert(m.capacity == 8);

  res = map_lookup(&m, "apple");

  assert(res.found);
  assert(res.val == 40);

  res = map_lookup(&m, "banana");

  assert(res.found);
  assert(res.val == 20);

  res = map_lookup(&m, "orange");

  assert(res.found);
  assert(res.val == 50);

  res = map_lookup(&m, "pineapple");

  assert(res.found);
  assert(res.val == 60);
  printf("All tests passed");
  return 0;
}