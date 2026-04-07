#include "stoi.c"
#include <stdio.h>

int main() {
  char *test1 = "1000";
  char *test2 = "29";
  char *test3 = "33334";
  char *test4 = "1";
  char *test5 = "0";

  int n;

  assert(stoi(test1, &n));
  assert(n == 1000);

  assert(stoi(test2, &n));
  assert(n == 29);

  assert(stoi(test3, &n));
  assert(n == 33334);

  assert(stoi(test4, &n));
  assert(n == 1);

  assert(stoi(test5, &n));
  assert(n == 0);

  printf("Tests passed successfully");
}