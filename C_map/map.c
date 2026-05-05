typedef struct MapEntry {
  char *key;
  int val;
} MapEntry;

typedef struct Map {
  MapEntry *data;
  int size;
  int capacity;
} Map;

int streq(char *s, char *q) { return !strcmp(s, q); }

void map_init(Map *m, int cap) {
  m->data = malloc(cap * sizeof(MapEntry));
  assert(m->data);
  m->size = 0;
  m->capacity = cap;
}

int map_find_idx(Map *m, char *key) {
  for (int i = 0; i < m->size; ++i) {
    if (streq(m->data[i].key, key)) {
      return i;
    }
  }

  return -1;
}

typedef struct FindRes {
  int found;
  int val;
} FindRes;

FindRes map_find(Map *m, char *key) {
  FindRes res;
  res.found = 0;

  int idx = map_find_idx(m, key);

  if (idx == -1) {
    return res;
  }

  res.found = 1;
  res.val = m->data[idx].val;

  return res;
}

void map_insert(Map *m, char *key, int val) {
  int idx = map_find_idx(m, key);

  if (idx == -1) {
    MapEntry to_insert;
    to_insert.key = key;
    to_insert.val = val;

    if (m->size >= m->capacity) {    
      MapEntry *tmp = realloc(m->data, m->capacity * 2 * sizeof(MapEntry));
      assert(tmp);

      m->data = tmp;
      m->capacity *= 2;
    }

    m->data[m->size] = to_insert;
    m->size += 1;
  } else {
    m->data[idx].val = val;
  }
}
