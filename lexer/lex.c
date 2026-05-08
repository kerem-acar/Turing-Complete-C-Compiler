int lex(const char *src, TokenArray *result) {
  if (src == NULL) {
    return 0;
  }

  while (*src) {
    if (isspace(*src)) {
      src++;
      continue;
    }

    Token tok;

    if (isdigit(*src)) {
      CharArray *number = initialize_char_array(1);

      while (*src && isdigit(*src)) {
        push_back_char(number, (*src));
        src++;
      }

      push_back_char(number, '\0');
      tok.kind = TOK_INTLIT;
      tok.literal = number->array;
      free(number);
      push_back_token(result, tok);
      continue;
    }

    if (isalpha(*src)) {
      CharArray *word = initialize_char_array(1);

      while (*src && isalpha(*src)) {
        push_back_char(word, (*src));
        src++;
      }
      
      push_back_char(word, '\0');

      if (!strcmp(word->array, "return")) {
        tok.kind = TOK_RETKEY;
        delete_char_array(&word);
      } else if (!strcmp(word->array, "int")) {
        tok.kind = TOK_INTKEY;
        delete_char_array(&word);
      } else if (!strcmp(word->array, "if")) {
        tok.kind = TOK_IFKEY;
        delete_char_array(&word);
      } else if (!strcmp(word->array, "else")) {
        tok.kind = TOK_ELSEKEY;
        delete_char_array(&word);
      } else {
        tok.kind = TOK_ID;
        tok.literal = word->array;
        free(word);
      }   

      push_back_token(result, tok);
      continue;
    }

    switch((*src)) {
    case '{': {
      tok.kind = TOK_LCURLY;
    } break;
    case '}': {
      tok.kind = TOK_RCURLY;
    } break;
    case '(': {
      tok.kind = TOK_LPAREN;
    } break;
    case ')': {
      tok.kind = TOK_RPAREN;
    } break;
    case ';': {
      tok.kind = TOK_SEMICOL;
    } break;
    case '-': {
      tok.kind = TOK_NEGATION;
    } break;
    case '~': {
      tok.kind = TOK_BITCOMP;
    } break;
    case ':': {
      tok.kind = TOK_COLON;
    } break;
    case '?': {
      tok.kind = TOK_QMARK;
    } break;
    case '!': {
      if (*(src + 1) == '=') {
        src++;
        tok.kind = TOK_LOGNEQ; 
      } else {
        tok.kind = TOK_LOGNEG;
      }
    } break;
    case '+': {
      tok.kind = TOK_ADD;
    } break;
    case '*': {
      tok.kind = TOK_MULTIPLY;
    } break;
    case '/': {
      tok.kind = TOK_DIVIDE;
    } break;
    case '&': {
      if (*(src + 1) == '&') {
        src++;
        tok.kind = TOK_LOGAND;
      }
    } break;
    case '|': {
      if (*(src + 1) == '|') {
        src++;
        tok.kind = TOK_LOGOR;
      }
    } break;
    case '=': {
      if (*(src + 1) == '=') {
        src++;
        tok.kind = TOK_LOGEQ;
      } else {
        tok.kind = TOK_ASSIGN;
      }
    } break;
    case '<': {
      if (*(src + 1) == '=') {
        src++;
        tok.kind = TOK_LOGLEQ;
      } else {
        tok.kind = TOK_LOGLE;
      }
    } break;
    case '>': {
      if (*(src + 1) == '=') {
        src++;
        tok.kind = TOK_LOGGEQ;
      } else {
        tok.kind = TOK_LOGGE;
      }
    } break;
    default: {
      tok.kind = TOK_UNK;
    } break;
    }

    push_back_token(result, tok);
    src++;
  }
  return 1;
}
