typedef enum Status {
  EMPTY,
  DELETED,
  OCCUPIED
} Status;

typedef struct MapEntry {
  char *key;
  int val;
  Status state;
} MapEntry;

typedef struct StackIndexMap {
  MapEntry *data;
  int capacity;
  int size;
} StackIndexMap;

int streq(char *s, char *q) { 
  if (s == NULL || q == NULL) {
    return 0;
  }
  return !strcmp(s, q); 
}

void map_init(StackIndexMap *m, int cap) {
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

int get_index(StackIndexMap *m, char *key) {
  return hash(key) % m->capacity;
}

FindRes map_lookup(StackIndexMap *m, char *key) {
  FindRes res;
  res.found = 0;

  int idx = get_index(m, key);

  if (m->data[idx].state == EMPTY) {
    return res;
  }

  if (streq(key, m->data[idx].key)) {
    res.found = 1;
    res.val = m->data[idx].val;
    res.index = idx;
  } else {
    idx = (idx + 1) % m->capacity;

    while (m->data[idx].state != EMPTY) {
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

void map_insert(StackIndexMap *m, char *key, int val) {
  if (m->size * 4 >= m->capacity * 3) { // trigger resize when map is 75% full    
    StackIndexMap tmp;
    map_init(&tmp, m->capacity * 2);
    
    for (unsigned int i = 0; i < m->capacity; i += 1) {
      if (m->data[i].state == OCCUPIED) {
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
  to_insert.state = OCCUPIED;

  if (m->data[idx].state != OCCUPIED) {
    m->data[idx] = to_insert;
    m->size += 1;
  } else {
    while (m->data[idx].state == OCCUPIED) {
      idx = (idx + 1) % m->capacity;
    }

    m->data[idx] = to_insert;
    m->size += 1;
  }
}

void delete_key(StackIndexMap *m, char *key) {
  FindRes res = map_lookup(m, key);

  if (res.found) {
    m->data[res.index].state = DELETED;
    free(m->data[res.index].key);
    m->data[res.index].key = NULL;
    m->data[res.index].val = 0;
    m->size -= 1;
  }
}

void map_copy(StackIndexMap *dest, StackIndexMap *src) {
  dest->capacity = src->capacity;
  dest->size = src->size;

  dest->data = (MapEntry *)calloc(dest->capacity, sizeof(MapEntry));
  assert(dest->data);

  for (int i = 0; i < src->capacity; i++) {
    dest->data[i].state = src->data[i].state;
    
    if (src->data[i].state == OCCUPIED) {
      dest->data[i].val = src->data[i].val;
      dest->data[i].key = strdup(src->data[i].key); 
    }
  }
}