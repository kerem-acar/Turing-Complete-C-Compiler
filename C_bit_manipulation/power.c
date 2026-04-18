int is_power_of_2(unsigned int n) {
  if (n <= 1) {
    return 0;
  }

  return !((n - 1) & n);
}