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

void generate_expression(AST_Expression *exp, CharArray *arr) {
  static char *indent = "    ";
  static char *move_to_eax = "mov eax, ";
  static char *neg = "neg eax";
  static char *bit_comp = "not eax"; 
  static char *compare_to = "cmp eax, ";
  static char *sete_al = "sete al";

  if (exp->kind == 0) {
    print_to_char_array(arr, "%s%s%s\n", indent, move_to_eax, exp->Constant);
  } else {
    generate_expression(exp->UnOp.exp, arr);
    switch(exp->UnOp.op.kind) {
    case TOK_NEGATION: {
      print_to_char_array(arr, "%s%s\n", indent, neg);
    } break;
    case TOK_BITCOMP: {
      print_to_char_array(arr, "%s%s\n", indent, bit_comp);
    } break;
    case TOK_LOGNEG: {
      print_to_char_array(arr, "%s%s%c\n", indent, compare_to, '0');
      print_to_char_array(arr, "%s%s%c\n", indent, move_to_eax, '0');
      print_to_char_array(arr, "%s%s\n", indent, sete_al);

    } break;
    }
  }
}

void generate_statement(AST_Statement *stmt, CharArray *arr) {
  static char *indent = "    ";
  static char *ret = "ret";

  generate_expression(stmt->exp, arr);

  print_to_char_array(arr, "%s%s\n", indent, ret);
}

int generate_function(AST_Program *prog, char *file_path, CharArray *arr, int id) {
  static char *syntax_directive = ".intel_syntax noprefix";
  static char *globl_directive = ".globl ";

  AST_Function *func = prog->func;

  print_to_char_array(arr, "%s\n", syntax_directive);
  print_to_char_array(arr, "%s%s%i\n", globl_directive, func->name, id);
  print_to_char_array(arr, "%s%i:\n", func->name, id);
  
  generate_statement(func->body, arr);

  push_back_char(arr, '\0');

  if (!write_string_to_file(file_path, arr)) {
    return 0;
  }

  return 1;
}