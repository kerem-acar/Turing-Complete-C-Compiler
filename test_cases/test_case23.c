int main() {
  int a = 1;

  do {
    a = a * 2;
    
    if (!(a - 2)) {
      break;
    }
  } while(a < 11);

  return a;
}