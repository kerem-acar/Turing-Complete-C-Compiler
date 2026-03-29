#include "../parser/print.c"
#include "write_to_file.c"

void push_back_word(char *word, CharArray *arr) {
  for (int i = 0; word[i] != '\0'; i++) {
    push_back_char(arr, word[i]);
  }
}

int generate(AST_Program *prog, char *file_path, CharArray *arr) {
  char *syntax_directive = ".intel_syntax noprefix\n";
  char *globl_directive = ".globl ";
  char *indent = "    ";
  char *move_to_eax = "mov eax, ";
  char *ret = "ret";

  push_back_word(syntax_directive, arr);
  push_back_word(globl_directive, arr);
  push_back_word(prog->func->name, arr);
  push_back_char(arr, '\n');
  push_back_word(prog->func->name, arr);
  push_back_char(arr, ':');
  push_back_char(arr, '\n');
  push_back_word(indent, arr);
  push_back_word(move_to_eax, arr);
  push_back_word(prog->func->body->exp->constant, arr);
  push_back_char(arr, '\n');
  push_back_word(indent, arr);
  push_back_word(ret, arr);

  push_back_char(arr, '\0');

  if (write_string_to_file(file_path, arr) == 0) {
    return 0;
  }

  return 1;
}