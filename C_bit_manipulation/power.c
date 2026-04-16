int is_power_of_2(unsigned int n) {
  if (!n) { //edge case where n is 0
    return 0;
  }

  int seen = 0;  

  for (unsigned int i = 0; i < 32; ++i) {
    if (check_bit(n, i)) {
      if (seen) {
        return 0;
      }
      seen = 1;
    }
  }

  return 1;
}