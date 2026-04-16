int unset_bit(int n, unsigned int pos) {
  assert(pos < 32);
    
  unsigned int y = 1;
  y = y << pos;
  y = ~y;

  return n & y;  
}