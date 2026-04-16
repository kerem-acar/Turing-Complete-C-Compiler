bool compare(const char *s1, const char *s2) {
  while ((*s1) && (*s2)) {
    if ((*s1) != (*s2)) {
      return false;
    }
    s1++;
    s2++;
  }

  if ((*s1) == (*s2) && (*s1) == '\0') {
    return true;
  }

  return false;
}