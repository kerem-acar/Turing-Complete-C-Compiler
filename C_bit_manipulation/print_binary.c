void print_binary(int n) {
  unsigned int y = 1;
  y = y << 31;

  printf("0b");

  for (int i = 0; i < 32; ++i) {
    if (!(n & y)) {
      printf("0");
    } else {
      printf("1");
    }

    y = y >> 1;
  }
  printf("\n");
}