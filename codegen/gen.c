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

void generate_expression(AST_Expression *exp, CharArray *arr, Map *var_map, int *clause_id, int *end_id) {
  static char *indent = "    ";

  if (exp->kind == EXP_CONSTANT) {
    print_to_char_array(arr, "%s%s%s\n", indent, "mov eax, ", exp->Constant);
  } else if (exp->kind == EXP_UN_OP) {
    generate_expression(exp->UnOp.exp, arr, var_map, clause_id, end_id);
    switch(exp->UnOp.un_op.kind) {
    case TOK_NEGATION: {
      print_to_char_array(arr, "%s%s\n", indent, "neg eax");
    } break;
    case TOK_BITCOMP: {
      print_to_char_array(arr, "%s%s\n", indent, "not eax");
    } break;
    case TOK_LOGNEG: {
      print_to_char_array(arr, "%s%s\n", indent, "cmp eax, 0");
      print_to_char_array(arr, "%s%s\n", indent, "mov eax, 0");
      print_to_char_array(arr, "%s%s\n", indent, "sete al");
    } break;
    }
  } else if (exp->kind == EXP_ASSIGN) {
    generate_expression(exp->Assign.exp, arr, var_map, clause_id, end_id);
    FindRes res = map_find(var_map, exp->Assign.name);
    
    if (!res.found) {
      assert(0);
    }

    int offset = res.val;

    print_to_char_array(arr, "%s%s%d%s\n", indent, "mov dword ptr [rbp - ", offset, "], eax");
  } else if (exp->kind == EXP_REF) {
    FindRes res = map_find(var_map, exp->Reference);
    
    if (!res.found) {
      assert(0);
    }

    int offset = res.val;
    
    print_to_char_array(arr, "%s%s%d%c\n", indent, "mov eax, dword ptr [rbp - ", offset, ']');
  } else {
    generate_expression(exp->BinOp.left_exp, arr, var_map, clause_id, end_id);

    if (__BIN_JUNC_START__ > exp->BinOp.bin_op.kind || exp->BinOp.bin_op.kind > __BIN_JUNC_END__) {
      print_to_char_array(arr, "%s%s\n", indent, "push rax");
      generate_expression(exp->BinOp.right_exp, arr, var_map, clause_id, end_id);
    } 
    
    if (__BIN_ARITH_START__ < exp->BinOp.bin_op.kind && exp->BinOp.bin_op.kind < __BIN_RELAT_END__) {
      print_to_char_array(arr, "%s%s\n", indent, "pop rcx");
    } 
    
    if (__BIN_RELAT_START__ < exp->BinOp.bin_op.kind && exp->BinOp.bin_op.kind < __BIN_RELAT_END__) {
      print_to_char_array(arr, "%s%s\n", indent, "cmp ecx, eax");
      print_to_char_array(arr, "%s%s\n", indent, "mov eax, 0");
    }

    switch(exp->BinOp.bin_op.kind) {
    case TOK_ADD: {
      print_to_char_array(arr, "%s%s\n", indent, "add eax, ecx");
    } break;
    case TOK_MULTIPLY: {
      print_to_char_array(arr, "%s%s\n", indent, "imul eax, ecx");
    } break;
    case TOK_NEGATION: {
      print_to_char_array(arr, "%s%s\n", indent, "sub ecx, eax");
      print_to_char_array(arr, "%s%s\n", indent, "mov eax, ecx");
    } break;
    case TOK_DIVIDE: {
      print_to_char_array(arr, "%s%s\n", indent, "mov ecx, eax");
      print_to_char_array(arr, "%s%s\n", indent, "pop rax");
      print_to_char_array(arr, "%s%s\n", indent, "cdq");
      print_to_char_array(arr, "%s%s\n", indent, "idiv ecx");
    } break;
    case TOK_LOGEQ: {
      print_to_char_array(arr, "%s%s\n", indent, "sete al");
    } break;
    case TOK_LOGNEQ: {
      print_to_char_array(arr, "%s%s\n", indent, "setne al");
    } break;
    case TOK_LOGLE: {
      print_to_char_array(arr, "%s%s\n", indent, "setl al");
    } break;
    case TOK_LOGLEQ: {
      print_to_char_array(arr, "%s%s\n", indent, "setle al");
    } break;
    case TOK_LOGGE: {
      print_to_char_array(arr, "%s%s\n", indent, "setg al");
    } break;
    case TOK_LOGGEQ: {
      print_to_char_array(arr, "%s%s\n", indent, "setge al");
    } break;
    case TOK_LOGAND:
    case TOK_LOGOR: {
      int curr_clause_id = *clause_id;
      int curr_end_id = *end_id;

      print_to_char_array(arr, "%s%s\n", indent, "cmp eax, 0");

      if (exp->BinOp.bin_op.kind == TOK_LOGOR) {
        print_to_char_array(arr, "%s%s%s%d\n", indent, "je ", "clause", curr_clause_id);
        print_to_char_array(arr, "%s%s\n", indent, "mov eax, 1");
      } else {
        print_to_char_array(arr, "%s%s%s%d\n", indent, "jne ", "clause", curr_clause_id);
      }

      print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "end", curr_end_id);
      print_to_char_array(arr, "%s%d:\n", "clause", curr_clause_id);

      (*clause_id)++;
      (*end_id)++;
      
      generate_expression(exp->BinOp.right_exp, arr, var_map, clause_id, end_id);

      print_to_char_array(arr, "%s%s\n", indent, "cmp eax, 0");
      print_to_char_array(arr, "%s%s\n", indent, "mov eax, 0");
      print_to_char_array(arr, "%s%s\n", indent, "setne al");
      print_to_char_array(arr, "%s%d:\n", "end", curr_end_id);

    } break;
    }
  }
}

void generate_statement(AST_Statement *stmt, CharArray *arr, Map *var_map, int *stack_index, int *clause_id, int *end_id) {
  static char *indent = "    ";
  
  if (stmt->kind == STAT_RETURN) {
    generate_expression(stmt->Return, arr, var_map, clause_id, end_id);
  } else if (stmt->kind == STAT_DECLARE) {
    if (map_find_idx(var_map, stmt->Declare.name) != -1) {
      assert(0);
    }

    if (stmt->Declare.exp != NULL) {
      generate_expression(stmt->Declare.exp, arr, var_map, clause_id, end_id);
    } else {
      print_to_char_array(arr, "%s%s\n", indent, "mov eax, 0");
    }

    print_to_char_array(arr, "%s%s\n", indent, "push rax");
    map_insert(var_map, stmt->Declare.name, *stack_index);
    *stack_index += 8;
  } else {
    generate_expression(stmt->Expression, arr, var_map, clause_id, end_id);
  }
}

int generate_function(AST_Program *prog, char *file_path, CharArray *arr, int id) {
  static char *syntax_directive = ".intel_syntax noprefix";
  static char *globl_directive = ".globl ";
  static char *indent = "    ";

  AST_Function *func = prog->func;

  print_to_char_array(arr, "%s\n", syntax_directive);
  print_to_char_array(arr, "%s%s%i\n", globl_directive, func->name, id);
  print_to_char_array(arr, "%s%i:\n", func->name, id);
  print_to_char_array(arr, "%s%s\n", indent, "push rbp");
  print_to_char_array(arr, "%s%s\n", indent, "mov rbp, rsp");

  Map var_map;
  map_init(&var_map, 1);

  int stack_index = 8;
  int clause_id = 1;
  int end_id = 1;

  for (unsigned int i = 0; i < func->body->size; ++i) {
    generate_statement(&func->body->array[i], arr, &var_map, &stack_index, &clause_id, &end_id);
  }

  print_to_char_array(arr, "%s%s\n", indent, "mov rsp, rbp");
  print_to_char_array(arr, "%s%s\n", indent, "pop rbp");
  print_to_char_array(arr, "%s%s\n", indent, "ret");

  push_back_char(arr, '\0');

  if (!write_string_to_file(file_path, arr)) {
    return 0;
  }

  return 1;
}