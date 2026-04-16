int set_bit(int n, unsigned int pos) {
  assert(pos < 32);

  unsigned int y = 1;
  y = y << pos;

  return y | n;
}