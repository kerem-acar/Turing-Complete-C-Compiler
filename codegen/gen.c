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

void generate_expression(AST_Expression *exp, CharArray *arr, int *clause_id, int *end_id) {
  static char *indent = "    ";
  static char *move_to_eax = "mov eax, ";
  static char *neg = "neg eax";
  static char *bit_comp = "not eax"; 
  static char *compare_to = "cmp eax, ";
  static char *compare_ecx_to_eax = "cmp ecx, eax";
  static char *sete_al = "sete al";
  static char *push_from_rax = "push rax";
  static char *pop_to_rcx = "pop rcx";
  static char *add_eax_ecx = "add eax, ecx";
  static char *mul_eax_ecx = "imul eax, ecx";
  static char *sub_ecx_eax = "sub ecx, eax";
  static char *mov_ecx_eax = "mov eax, ecx";
  static char *mov_eax_ecx = "mov ecx, eax";
  static char *divide_by_ecx = "idiv ecx";
  static char *sign_extend = "cdq";
  static char *pop_to_rax = "pop rax";
  static char *setne_al = "setne al";
  static char *setl_al = "setl al";
  static char *setle_al = "setle al";
  static char *setg_al = "setg al";
  static char *setge_al = "setge al";
  static char *jump_if_equal = "je ";
  static char *jump = "jmp ";
  static char *jump_if_not_equal = "jne ";

  if (exp->kind == EXP_CONSTANT) {
    print_to_char_array(arr, "%s%s%s\n", indent, move_to_eax, exp->Constant);
  } else if (exp->kind == EXP_UN_OP) {
    generate_expression(exp->UnOp.exp, arr, clause_id, end_id);
    switch(exp->UnOp.un_op.kind) {
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
  } else {
    generate_expression(exp->BinOp.left_exp, arr, clause_id, end_id);

    if (__BIN_JUNC_START__ > exp->BinOp.bin_op.kind || exp->BinOp.bin_op.kind > __BIN_JUNC_END__) {
      print_to_char_array(arr, "%s%s\n", indent, push_from_rax);
      generate_expression(exp->BinOp.right_exp, arr, clause_id, end_id);
    } else if (__BIN_ARITH_START__ < exp->BinOp.bin_op.kind && exp->BinOp.bin_op.kind < __BIN_RELAT_END__) {
      print_to_char_array(arr, "%s%s\n", indent, pop_to_rcx);
    } else if (__BIN_RELAT_START__ < exp->BinOp.bin_op.kind && exp->BinOp.bin_op.kind < __BIN_RELAT_END__) {
      print_to_char_array(arr, "%s%s\n", indent, compare_ecx_to_eax);
      print_to_char_array(arr, "%s%s%c\n", indent, move_to_eax, '0');
    }

    switch(exp->BinOp.bin_op.kind) {
    case TOK_ADD: {
      print_to_char_array(arr, "%s%s\n", indent, add_eax_ecx);
    } break;
    case TOK_MULTIPLY: {
      print_to_char_array(arr, "%s%s\n", indent, mul_eax_ecx);
    } break;
    case TOK_NEGATION: {
      print_to_char_array(arr, "%s%s\n", indent, sub_ecx_eax);
      print_to_char_array(arr, "%s%s\n", indent, mov_ecx_eax);
    } break;
    case TOK_DIVIDE: {
      print_to_char_array(arr, "%s%s\n", indent, mov_eax_ecx);
      print_to_char_array(arr, "%s%s\n", indent, pop_to_rax);
      print_to_char_array(arr, "%s%s\n", indent, sign_extend);
      print_to_char_array(arr, "%s%s\n", indent, divide_by_ecx);
    } break;
    case TOK_LOGEQ: {
      print_to_char_array(arr, "%s%s\n", indent, sete_al);
    } break;
    case TOK_LOGNEQ: {
      print_to_char_array(arr, "%s%s\n", indent, setne_al);
    } break;
    case TOK_LOGLE: {
      print_to_char_array(arr, "%s%s\n", indent, setl_al);
    } break;
    case TOK_LOGLEQ: {
      print_to_char_array(arr, "%s%s\n", indent, setle_al);
    } break;
    case TOK_LOGGE: {
      print_to_char_array(arr, "%s%s\n", indent, setg_al);
    } break;
    case TOK_LOGGEQ: {
      print_to_char_array(arr, "%s%s\n", indent, setge_al);
    } break;
    case TOK_LOGAND:
    case TOK_LOGOR: {
      int curr_clause_id = *clause_id;
      int curr_end_id = *end_id;

      print_to_char_array(arr, "%s%s%c\n", indent, compare_to, '0');

      if (exp->BinOp.bin_op.kind == TOK_LOGOR) {
        print_to_char_array(arr, "%s%s%s%d\n", indent, jump_if_equal, "clause", curr_clause_id);
        print_to_char_array(arr, "%s%s%c\n", indent, move_to_eax, '1');
      } else {
        print_to_char_array(arr, "%s%s%s%d\n", indent, jump_if_not_equal, "clause", curr_clause_id);
      }

      print_to_char_array(arr, "%s%s%s%d\n", indent, jump, "end", curr_end_id);
      print_to_char_array(arr, "%s%d:\n", "clause", curr_clause_id);

      (*clause_id)++;
      (*end_id)++;
      
      generate_expression(exp->BinOp.right_exp, arr, clause_id, end_id);

      print_to_char_array(arr, "%s%s%c\n", indent, compare_to, '0');
      print_to_char_array(arr, "%s%s%c\n", indent, move_to_eax, '0');
      print_to_char_array(arr, "%s%s\n", indent, setne_al);
      print_to_char_array(arr, "%s%d:\n", "end", curr_end_id);

    } break;
    }
  }
}

void generate_statement(AST_Statement *stmt, CharArray *arr) {
  static char *indent = "    ";
  static char *ret = "ret";

  int clause_id = 1;
  int end_id = 1;

  generate_expression(stmt->exp, arr, &clause_id, &end_id);

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