int check_bit(int n, unsigned int pos) {
  assert(pos < 32);

  unsigned int y = 1;
  y = y << pos;

  if (y & n) {
    return 1;
  }
  
  return 0;
}