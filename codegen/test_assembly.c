#include <stdio.h>
#include <assert.h>

int main1();
int main2();
int main3();

int main() {

  assert(main1() == 12);
  assert(main2() == -24);
  assert(main3() == 1);

  printf("All tests passed");
  return 0;
}