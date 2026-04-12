void compare(char *s1, char *s2) {
  while ((*s1) && (*s2)) {
    assert((*s1) == (*s2));
    s1++;
    s2++;
  }

  assert((*s1) == (*s2) && (*s1) == '\0');
}