#include "../C_array/array.c"
#include "../C_map/map.c"
#include "read_file.c"
#include <ctype.h>

typedef struct Token {
  TokenType type;
  int literal;
} Token;



int lex(const char *file_name, IntArray *result) {
  const char *src = read_file(file_name);

  if (src == NULL) {
    return 0;
  }

  const StrMap keyword_map;
  const StrMap char_map;

  StrMap_init(&keyword_map, 2);
  StrMap_init(&char_map, 5);

  StrMap_insert(&keyword_map, "return", ReturnKeyword);
  StrMap_insert(&keyword_map, "int", IntKeyword);

  StrMap_insert(&char_map, "(", OpenParen);
  StrMap_insert(&char_map, ")", CloseParen);
  StrMap_insert(&char_map, "{", OpenBracket);
  StrMap_insert(&char_map, "}", CloseBracket);
  StrMap_insert(&char_map, ";", Semicolon);

  while (*src) {
    if (isspace(*src)) {
      src++;
      continue;
    }
    Token tok;
    if (isdigit(*src)) {
      char number[256];
      int number_len = 0;
      while (*src && isdigit(*src) && number_len < 255) {
        number[number_len] = (*src);
        number_len++;
        src++;
      }
      tok.type = IntegerLiteral;
      tok.literal = atoi(number);
      push_back(result, tok);
      continue;
    }
    if (isalpha(*src)) {
      tok.literal = -1;
      char word[256];
      int word_len = 0;
      while (*src && isalpha(*src) &&
             word_len < 255) {
        word[word_len] = (*src);
        word_len++;
        src++;
      }
      word[word_len] = '\0';

      FindRes res = StrMap_find(&keyword_map, word);

      if (res.found) {
        tok.type = res.val;
      } else {
        tok.type = Identifier;
      }
      push_back(result, tok);
      continue;
    }

    char word[2];

    word[0] = (*src);
    word[1] = '\0';

    FindRes res = StrMap_find(&char_map, word);
    if (res.found) {
      tok.type = res.val;
      tok.literal = (*src);
    } else {
      tok.type = Unknown;
      tok.literal = -1;
    }
    push_back(result, tok);
    src++;
  }
  return 1;
}
