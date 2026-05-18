int main() {
  int a = 0;
  int b = 1;

  while (a < 5) {
    a = a + 2;
    b = b * a;

    if (!(a - b)) {
      break;
    } 
  }

  return a;
}