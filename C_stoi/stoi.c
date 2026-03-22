#include <assert.h>
#include <ctype.h>

int stoi(char *str, int *out) {
  assert(str);

  if (*str == '0' && *(str + 1) != '\0') {
    return 0;
  }

  int res = 0;

  while (*str) {
    char c = *str;

    if (!isdigit(c)) {
      return 0;
    }

    res = res * 10 + (c - '0');

    ++str;
  }

  assert(out);

  *out = res;

  return 1;
}
