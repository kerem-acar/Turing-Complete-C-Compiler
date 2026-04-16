#include <stdio.h>
#include <assert.h>

#include "print_binary.c"
#include "set.c"
#include "unset.c"
#include "check.c"
#include "power.c"

int main() {
  int n = 2;
  int n1 = 8;
  int n2 = 7;
  
  print_binary(n);
  set_bit(&n, 9);
  assert(n == 514);
  assert(check_bit(n, 9));
  assert(!check_bit(n, 27));
  unset_bit(&n, 9);
  assert(n == 2);
  assert(!check_bit(n, 9));
  print_binary(n);

  print_binary(n1);
  set_bit(&n1, 2);
  assert(n1 == 12);
  assert(check_bit(n1, 2));
  assert(!check_bit(n1, 28));
  unset_bit(&n1, 2);
  assert(n1 == 8);
  assert(!check_bit(n1, 2));
  print_binary(n1);
  
  print_binary(n2);
  set_bit(&n2, 5);
  assert(n2 == 39);
  assert(check_bit(n2, 5));
  assert(!check_bit(2, 13));
  unset_bit(&n2, 5);
  assert(n2 == 7);
  assert(!check_bit(n2, 5));
  print_binary(n2);

  assert(is_power_of_2(2));
  assert(is_power_of_2(4));
  assert(is_power_of_2(8));
  assert(!is_power_of_2(3));
  assert(!is_power_of_2(6));

  return 0;
}