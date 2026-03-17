#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Token {
  OpenBracket,
  CloseBracket,
  OpenParen,
  CloseParen,
  Semicolon,
  ReturnKeyword,
  IntKeyword,
  Identifier,
  IntegerLiteral,
  Unknown
} Token;

typedef struct StrMapEntry {
  char *key;
  Token val;
} StrMapEntry;

typedef struct StrMap {
  StrMapEntry *data;
  int size;
  int capacity;
} StrMap;

int streq(char *s, char *q) { return !strcmp(s, q); }

void StrMap_init(StrMap *m, int cap) {
  m->data = malloc(cap * sizeof(StrMapEntry));
  assert(m->data);
  m->size = 0;
  m->capacity = cap;
}

int StrMap_find_idx(StrMap *m, char *key) {
    
  for (int i = 0; i < m->size; ++i) {
    if (streq(m->data[i].key, key)) {
      return i;
    }
  }
  return -1;
}

typedef struct FindRes {
  int found;
  Token val;
} FindRes;

FindRes StrMap_find(StrMap *m, char *key) {
  FindRes res;
  res.found = 0;
  int idx = StrMap_find_idx(m, key);
  if (idx == -1) {
    return res;
  }
  res.found = 1;
  res.val = m->data[idx].val;
  return res;
}


bool StrMap_insert(StrMap *m, char *key, Token val) {
  int idx = StrMap_find_idx(m, key);
  if (idx == -1) {
    assert(m->size + 1 <= m->capacity);
    m->data[m->size] = (StrMapEntry){.key = key, .val = val};
    m->size += 1;
    return true;
  }
  m->data[idx].val = val;
  return false;
}

// int main(void) {
//   StrMap m;
//   StrMap_init(&m, 2);

//   assert(StrMap_insert(&m, "return", ReturnKeyword));
//   assert(StrMap_insert(&m, "int", Identifier));
//   assert(StrMap_insert(&m, "int", IntKeyword) == false);

//   FindRes res;
//   res = StrMap_find(&m, "return");
//   assert(res.found);
//   assert(res.val == ReturnKeyword);

//   res = StrMap_find(&m, "int");
//   assert(res.found);
//   assert(res.val == IntKeyword);
// }
