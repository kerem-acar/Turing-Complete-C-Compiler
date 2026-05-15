typedef struct MapEntry {
  char *key;
  int val; // 0 signals empty, 1 signals deleted
} MapEntry;

typedef struct Map {
  MapEntry *data;
  int capacity;
  int size;
} Map;

int streq(char *s, char *q) { 
  if (s == NULL || q == NULL) {
    return 0;
  }
  return !strcmp(s, q); 
}

void map_init(Map *m, int cap) {
  m->data = (MapEntry *)calloc(cap, sizeof(MapEntry));
  assert(m->data);
  m->capacity = cap;
  m->size = 0;
}

typedef struct FindRes {
  int found;
  int val;
  int index;
} FindRes;

int get_index(Map *m, char *key) {
  return hash(key) % m->capacity;
}

FindRes map_lookup(Map *m, char *key) {
  FindRes res;
  res.found = 0;

  int idx = get_index(m, key);

  if (m->data[idx].val == 0) {
    return res;
  }

  if (streq(key, m->data[idx].key)) {
    res.found = 1;
    res.val = m->data[idx].val;
    res.index = idx;
  } else {
    idx = (idx + 1) % m->capacity;

    while (m->data[idx].val != 0) {
      if (streq(key, m->data[idx].key)) {
        res.found = 1;
        res.val = m->data[idx].val;
        res.index = idx;
        return res;
      }

      idx = (idx + 1) % m->capacity;
    }
  }

  return res;
}

void map_insert(Map *m, char *key, int val) {
  if (m->size * 4 >= m->capacity * 3) { // trigger resize when map is 75% full    
    Map tmp;
    map_init(&tmp, m->capacity * 2);
    
    for (unsigned int i = 0; i < m->capacity; i += 1) {
      if (m->data[i].val != 0 && m->data[i].val != 1) {
        map_insert(&tmp, m->data[i].key, m->data[i].val);
      }
    }

    free(m->data);

    m->data = tmp.data;
    m->capacity *= 2;
    m->size = tmp.size;
  }
  
  FindRes res = map_lookup(m, key);

  if (res.found) {
    m->data[res.index].val = val;
    return;
  }

  int idx = get_index(m, key);

  MapEntry to_insert;
  to_insert.key = key;
  to_insert.val = val;

  if (m->data[idx].val == 0 || m->data[idx].val == 1) {
    m->data[idx] = to_insert;
    m->size += 1;
  } else {
    while (m->data[idx].val != 0 && m->data[idx].val != 1) {
      idx = (idx + 1) % m->capacity;
    }

    m->data[idx] = to_insert;
    m->size += 1;
  }
}

void delete_key(Map *m, char *key) {
  FindRes res = map_lookup(m, key);

  if (res.found) {
    m->data[res.index].val = 1;
    free(m->data[res.index].key);
    m->data[res.index].key = NULL;
    m->size -= 1;
  }
}