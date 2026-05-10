#include <stdio.h>
#include <assert.h>

int main1();
int main2();
int main3();

int main() {

  assert(main1() == 3);
  assert(main2() == 1);
  assert(main3() == 2);

  printf("All tests passed");
  return 0;
}