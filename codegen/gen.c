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

void generate_expression(AST_Expression *exp, CharArray *arr, StackIndexMap *m, int *clause_id, int *end_id) {
  static char *indent = "    ";

  if (exp == NULL) {
    return;
  }
  if (exp->kind == EXP_CONSTANT) {
    print_to_char_array(arr, "%s%s%s\n", indent, "mov eax, ", exp->Constant);
  } else if (exp->kind == EXP_UN_OP) {
    generate_expression(exp->UnOp.exp, arr, m, clause_id, end_id);
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
    generate_expression(exp->Assign.exp, arr, m, clause_id, end_id);
    FindRes res = map_lookup(m, exp->Assign.name);
    
    if (!res.found) {
      assert(0);
    }

    int offset = res.val;

    print_to_char_array(arr, "%s%s%d%s\n", indent, "mov dword ptr [rbp - ", offset, "], eax");
  } else if (exp->kind == EXP_REF) {
    FindRes res = map_lookup(m, exp->Reference);
    
    if (!res.found) {
      assert(0);
    }

    int offset = res.val;
    
    print_to_char_array(arr, "%s%s%d%c\n", indent, "mov eax, dword ptr [rbp - ", offset, ']');
  } else if (exp->kind == EXP_BIN_OP) {
    generate_expression(exp->BinOp.left_exp, arr, m, clause_id, end_id);

    if (__BIN_JUNC_START__ > exp->BinOp.bin_op.kind || exp->BinOp.bin_op.kind > __BIN_JUNC_END__) {
      print_to_char_array(arr, "%s%s\n", indent, "push rax");
      generate_expression(exp->BinOp.right_exp, arr, m, clause_id, end_id);
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
      
      generate_expression(exp->BinOp.right_exp, arr, m, clause_id, end_id);

      print_to_char_array(arr, "%s%s\n", indent, "cmp eax, 0");
      print_to_char_array(arr, "%s%s\n", indent, "mov eax, 0");
      print_to_char_array(arr, "%s%s\n", indent, "setne al");
      print_to_char_array(arr, "%s%d:\n", "end", curr_end_id);

    } break;
    }
  } else {
    generate_expression(exp->CondExp.e1, arr, m, clause_id, end_id);

    int curr_clause_id = *clause_id;
    int curr_end_id = *end_id;

    print_to_char_array(arr, "%s%s\n", indent, "cmp eax, 0");
    print_to_char_array(arr, "%s%s%s%d\n", indent, "je ", "clause", curr_clause_id);
    
    (*clause_id)++;
    (*end_id)++;

    generate_expression(exp->CondExp.e2, arr, m, clause_id, end_id);

    print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "end", curr_end_id);
    print_to_char_array(arr, "%s%d:\n", "clause", curr_clause_id);

    (*clause_id)++;
    (*end_id)++;

    generate_expression(exp->CondExp.e3, arr, m, clause_id, end_id);
    print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "end", curr_end_id);
    print_to_char_array(arr, "%s%d:\n", "end", curr_end_id);
  }
}

void generate_declaration(AST_Declaration *dec, CharArray *arr, StackIndexMap *m, StringSet *s, int *stack_index, int *clause_id, int *end_id);
void generate_block(BlockArray *b, CharArray *arr, StackIndexMap *m, int *stack_index, int *clause_id, int *end_id, int c_end_id, int c_clause_id);

void generate_statement(AST_Statement *stmt, CharArray *arr, StackIndexMap *m, int *stack_index, int *clause_id, int *end_id, int c_end_id, int c_clause_id) {
  static char *indent = "    ";
  

  
  int curr_clause_id = *clause_id;
  int curr_end_id = *end_id;

  if (stmt->kind == STAT_RETURN) {
    generate_expression(stmt->Return, arr, m, clause_id, end_id);
  } else if (stmt->kind == STAT_EXP) {
    generate_expression(stmt->Expression, arr, m, clause_id, end_id);
  } else if (stmt->kind == STAT_IF) {
    generate_expression(stmt->If.exp, arr, m, clause_id, end_id);

    print_to_char_array(arr, "%s%s\n", indent, "cmp eax, 0");
    print_to_char_array(arr, "%s%s%s%d\n", indent, "je ", "clause", curr_clause_id);
    
    (*clause_id)++;
    (*end_id)++;

    generate_statement(stmt->If.stat, arr, m, stack_index, clause_id, end_id, c_end_id, c_clause_id);

    print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "end", curr_end_id);
    print_to_char_array(arr, "%s%d:\n", "clause", curr_clause_id);

    if (stmt->If.optional_stat != NULL) {
      (*clause_id)++;
      (*end_id)++;

      generate_statement(stmt->If.optional_stat, arr, m, stack_index, clause_id, end_id, c_end_id, c_clause_id);
    }
    
    print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "end", curr_end_id);
    print_to_char_array(arr, "%s%d:\n", "end", curr_end_id);
  } else if (stmt->kind == STAT_WHILE) {
    print_to_char_array(arr, "%s%d:\n", "clause", curr_clause_id);

    (*clause_id)++;
    (*end_id)++;

    generate_expression(stmt->While.exp, arr, m, clause_id, end_id);

    print_to_char_array(arr, "%s%s\n", indent, "cmp eax, 0");
    print_to_char_array(arr, "%s%s%s%d\n", indent, "je ", "end", curr_end_id);

    (*clause_id)++;
    (*end_id)++;

    generate_statement(stmt->While.stat, arr, m, stack_index, clause_id, end_id, curr_end_id, curr_clause_id);

    print_to_char_array(arr, "%s%d:\n", "special", curr_clause_id);
    print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "clause", curr_clause_id);

    print_to_char_array(arr, "%s%d:\n", "end", curr_end_id);
  } else if (stmt->kind == STAT_DO) {
    print_to_char_array(arr, "%s%d:\n", "clause", curr_clause_id);

    (*clause_id)++;
    (*end_id)++;

    generate_statement(stmt->Do.stat, arr, m, stack_index, clause_id, end_id, curr_end_id, curr_clause_id);

    (*clause_id)++;
    (*end_id)++;

    generate_expression(stmt->Do.exp, arr, m, clause_id, end_id);

    print_to_char_array(arr, "%s%s\n", indent, "cmp eax, 0");
    print_to_char_array(arr, "%s%s%s%d\n", indent, "je ", "end", curr_end_id);

    print_to_char_array(arr, "%s%d:\n", "special", curr_clause_id);
    print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "clause", curr_clause_id);

    print_to_char_array(arr, "%s%d:\n", "end", curr_end_id);
  } else if (stmt->kind == STAT_FORDEC) {
    (*clause_id)++;
    (*end_id)++;

    StackIndexMap m1;
    map_copy(&m1, m);

    
    StringSet curr_scope;
    set_init(&curr_scope, 10);

    generate_declaration(stmt->ForDecl.dec, arr, &m1, &curr_scope, stack_index, clause_id, end_id);

    print_to_char_array(arr, "%s%d:\n", "clause", curr_clause_id);

    (*clause_id)++;
    (*end_id)++;

    generate_expression(stmt->ForDecl.e1, arr, &m1, clause_id, end_id);

    print_to_char_array(arr, "%s%s\n", indent, "cmp eax, 0");
    print_to_char_array(arr, "%s%s%s%d\n", indent, "je ", "end", curr_end_id);

    (*clause_id)++;
    (*end_id)++;

    generate_statement(stmt->ForDecl.stat, arr, &m1, stack_index, clause_id, end_id, curr_end_id, curr_clause_id);

    (*clause_id)++;
    (*end_id)++;

    print_to_char_array(arr, "%s%d:\n", "special", curr_clause_id);
    generate_expression(stmt->ForDecl.e2, arr, &m1, clause_id, end_id);

    print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "clause", curr_clause_id);
    print_to_char_array(arr, "%s%d:\n", "end", curr_end_id);

    *stack_index -= 8;
    print_to_char_array(arr, "%s%s\n", indent, "add rsp, 8");
  } else if (stmt->kind == STAT_FOR) {
    (*clause_id)++;
    (*end_id)++;

    generate_expression(stmt->For.e1, arr, m, clause_id, end_id);

    print_to_char_array(arr, "%s%d:\n", "clause", curr_clause_id);
    
    (*clause_id)++;
    (*end_id)++;

    generate_expression(stmt->For.e2, arr, m, clause_id, end_id);

    print_to_char_array(arr, "%s%s\n", indent, "cmp eax, 0");
    print_to_char_array(arr, "%s%s%s%d\n", indent, "je ", "end", curr_end_id);

    (*clause_id)++;
    (*end_id)++;

    generate_statement(stmt->For.stat, arr, m, stack_index, clause_id, end_id, curr_end_id, curr_clause_id);

    (*clause_id)++;
    (*end_id)++;

    print_to_char_array(arr, "%s%d:\n", "special", curr_clause_id);
    generate_expression(stmt->For.e3, arr, m, clause_id, end_id);

    print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "clause", curr_clause_id);
    print_to_char_array(arr, "%s%d:\n", "end", curr_end_id);
  } else if (stmt->kind == STAT_BREAK) {
    print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "end", c_end_id);
  } else if (stmt->kind == STAT_CONT) {
    print_to_char_array(arr, "%s%s%s%d\n", indent, "jmp ", "special", c_clause_id);
  } else {
    StackIndexMap m1;
    map_copy(&m1, m);

    generate_block(stmt->Compound, arr, &m1, stack_index, clause_id, end_id, c_end_id, c_clause_id);
  }
}

void generate_declaration(AST_Declaration *dec, CharArray *arr, StackIndexMap *m, StringSet *s, int *stack_index, int *clause_id, int *end_id) {
  static char *indent = "    ";

  FindRes res = set_lookup(s, dec->name);

  if (res.found) {
    assert(0);
  }

  if (dec->optional_exp != NULL) {
    generate_expression(dec->optional_exp, arr, m, clause_id, end_id);
  } else {
    print_to_char_array(arr, "%s%s\n", indent, "mov eax, 0");
  }

  print_to_char_array(arr, "%s%s\n", indent, "push rax");
  map_insert(m, dec->name, *stack_index);
  *stack_index += 8;  
  set_add(s, dec->name);
}

void generate_block(BlockArray *b, CharArray *arr, StackIndexMap *m, int *stack_index, int *clause_id, int *end_id, int c_end_id, int c_clause_id) {
  static char *indent = "    ";

  StringSet curr_scope;
  set_init(&curr_scope, 10);
  
  for (unsigned int i = 0; i < b->size; ++i) {
    if (b->array[i]->kind == BLOCK_STAT) {
      generate_statement(b->array[i]->stat, arr, m, stack_index, clause_id, end_id, c_end_id, c_clause_id);
    } else {
      generate_declaration(b->array[i]->dec, arr, m, &curr_scope, stack_index, clause_id, end_id);
    }
  }

  int bytes_to_dealloc = 8 * curr_scope.size;

  print_to_char_array(arr, "%s%s%d\n", indent, "add rsp, ", bytes_to_dealloc);

  *stack_index -= bytes_to_dealloc;
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

  StackIndexMap m;
  map_init(&m, 10);

  int stack_index = 8;
  int clause_id = 1;
  int end_id = 1;

  generate_block(func->body, arr, &m, &stack_index, &clause_id, &end_id, -1, -1);

  print_to_char_array(arr, "%s%s\n", indent, "mov rsp, rbp");
  print_to_char_array(arr, "%s%s\n", indent, "pop rbp");
  print_to_char_array(arr, "%s%s\n", indent, "ret");

  push_back_char(arr, '\0');

  if (!write_string_to_file(file_path, arr)) {
    return 0;
  }

  return 1;
}