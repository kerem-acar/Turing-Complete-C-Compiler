// djb2 hashing algorithm
uint32_t hash(const char *key) {
  uint32_t h = 5381;
  uint8_t c;

  while (*key) {
    c = (uint8_t)*key;
    h = ((h << 5) + h) + c;
    key++;
  }

  return h;
}