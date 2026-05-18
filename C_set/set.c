typedef struct SetEntry {
  char *key;
  Status state;
} SetEntry;

typedef struct StringSet {
  SetEntry *data;
  int capacity;
  int size;
} StringSet;


void set_init(StringSet *s, int cap) {
  s->data = (SetEntry *)calloc(cap, sizeof(SetEntry));
  assert(s->data);
  s->capacity = cap;
  s->size = 0;
}

int get_set_index(StringSet *s, char *key) {
  return hash(key) % s->capacity;
}

FindRes set_lookup(StringSet *s, char *key) {
  FindRes res;
  res.found = 0;

  int idx = get_set_index(s, key);

  if (s->data[idx].state == EMPTY) {
    return res;
  }

  if (streq(key, s->data[idx].key)) {
    res.found = 1;
    res.index = idx;
  } else {
    idx = (idx + 1) % s->capacity;

    while (s->data[idx].state != EMPTY) {
      if (streq(key, s->data[idx].key)) {
        res.found = 1;
        res.index = idx;
        return res;
      }

      idx = (idx + 1) % s->capacity;
    }
  }

  return res;
}


void set_add(StringSet *s, char *key) {
  if (s->size * 4 >= s->capacity * 3) { // trigger resize when map is 75% full    
    StringSet tmp;
    set_init(&tmp, s->capacity * 2);
    
    for (unsigned int i = 0; i < s->capacity; i += 1) {
      if (s->data[i].state == OCCUPIED) {
        set_add(&tmp, s->data[i].key);
      }
    }

    free(s->data);

    s->data = tmp.data;
    s->capacity *= 2;
    s->size = tmp.size;
  }
  
  FindRes res = set_lookup(s, key);

  if (res.found) {
    return;
  }

  int idx = get_set_index(s, key);

  SetEntry to_insert;
  to_insert.key = key;
  to_insert.state = OCCUPIED;

  if (s->data[idx].state != OCCUPIED) {
    s->data[idx] = to_insert;
    s->size += 1;
  } else {
    while (s->data[idx].state == OCCUPIED) {
      idx = (idx + 1) % s->capacity;
    }

    s->data[idx] = to_insert;
    s->size += 1;
  }
}