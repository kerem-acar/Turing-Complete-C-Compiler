void push_back_word(CharArray *arr, char *word, int length) {
  for (int i = 0; i < length; i++) {
    push_back_char(arr, word[i]);
  }
}

void print_to_char_array(CharArray *arr, const char *fmt, ...) {
  va_list args;
  int n;
  va_start(args, fmt);

  static char buf[256];

  n = vsprintf(buf, fmt, args);
  assert(n < 256);

  push_back_word(arr, buf, n);
  va_end(args);
}

int generate(AST_Program *prog, char *file_path, CharArray *arr) {
  char *syntax_directive = ".intel_syntax noprefix";
  char *globl_directive = ".globl ";
  char *indent = "    ";
  char *move_to_eax = "mov eax, ";
  char *ret = "ret";

  print_to_char_array(arr, "%s\n", syntax_directive);
  print_to_char_array(arr, "%s%s\n", globl_directive, prog->func->name);
  print_to_char_array(arr, "%s:\n", prog->func->name);
  print_to_char_array(arr, "%s%s%s\n", indent, move_to_eax,
                      prog->func->body->exp->constant);
  print_to_char_array(arr, "%s%s\n", indent, ret);

  push_back_char(arr, '\0');

  if (write_string_to_file(file_path, arr) == 0) {
    return 0;
  }

  return 1;
}