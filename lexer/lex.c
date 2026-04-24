int lex(const char *src, TokenArray *result) {
  if (src == NULL) {
    return 0;
  }

  StrMap keyword_map;
  StrMap char_map;
  StrMap operator_map;

  StrMap_init(&keyword_map, 2);
  StrMap_init(&char_map, 5);
  StrMap_init(&operator_map, 14);

  StrMap_insert(&keyword_map, "return", TOK_RETKEY);
  StrMap_insert(&keyword_map, "int", TOK_INTKEY);

  StrMap_insert(&char_map, "(", TOK_LPAREN);
  StrMap_insert(&char_map, ")", TOK_RPAREN);
  StrMap_insert(&char_map, "{", TOK_LCURLY);
  StrMap_insert(&char_map, "}", TOK_RCURLY);
  StrMap_insert(&char_map, ";", TOK_SEMICOL);

  StrMap_insert(&operator_map, "~", TOK_BITCOMP);
  StrMap_insert(&operator_map, "!", TOK_LOGNEG);
  StrMap_insert(&operator_map, "-", TOK_NEGATION);
  StrMap_insert(&operator_map, "+", TOK_ADD);
  StrMap_insert(&operator_map, "*", TOK_MULTIPLY);
  StrMap_insert(&operator_map, "/", TOK_DIVIDE);
  StrMap_insert(&operator_map, "&&", TOK_LOGAND);
  StrMap_insert(&operator_map, "||", TOK_LOGOR);
  StrMap_insert(&operator_map, "==", TOK_LOGEQ);
  StrMap_insert(&operator_map, "!=", TOK_LOGNEQ);
  StrMap_insert(&operator_map, "<", TOK_LOGLE);
  StrMap_insert(&operator_map, "<=", TOK_LOGLEQ);
  StrMap_insert(&operator_map, ">", TOK_LOGGE);
  StrMap_insert(&operator_map, ">=", TOK_LOGGEQ);

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

      FindRes res = StrMap_find(&keyword_map, word->array);

      if (res.found) {
        tok.kind = res.val;
      } else {
        tok.kind = TOK_ID;
      }
      tok.literal = word->array;
      push_back_token(result, tok);
      continue;
    }

    CharArray *word = initialize_char_array(1);

    push_back_char(word, (*src));

    if ((*src) == '<' || (*src) == '>' || (*src) == '!' || (*src) == '=') {
      if (*(src + 1) == '=') {
        src++;
        push_back_char(word, (*src));
      }
    }

    if ((*src) == '&' && (*(src + 1)) == '&') {
      src++;
      push_back_char(word, (*src));
    }

    if ((*src) == '|' && (*(src + 1)) == '|') {
      src++;
      push_back_char(word, (*src));
    }

    push_back_char(word, '\0');

    FindRes char_res = StrMap_find(&char_map, word->array);
    FindRes operator_res = StrMap_find(&operator_map, word->array);

    if (operator_res.found) {
      tok.kind = operator_res.val;
    } else if (char_res.found) {
      tok.kind = char_res.val;
    } else {
      tok.kind = TOK_UNK;
    }
    tok.literal = word->array;
    push_back_token(result, tok);
    src++;
  }
  return 1;
}
