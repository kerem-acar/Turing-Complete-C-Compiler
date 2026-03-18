#include "../C_array/array.c"
#include "../C_map/map.c"
#include "read_file.c"
#include <ctype.h>

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
    if (isdigit(*src)) {
      while (*src && isdigit(*src)) {
        src++;
      }
      push_back(result, IntegerLiteral);
      continue;
    }
    if (isalpha(*src)) {
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
        push_back(result, res.val);
      } else {
        push_back(result, Identifier);
      }
      continue;
    }

    char word[2];

    word[0] = (*src);
    word[1] = '\0';

    FindRes res = StrMap_find(&char_map, word);
    if (res.found) {
      push_back(result, res.val);
    } else {
      push_back(result, Unknown);
    }
    src++;
  }
  return 1;
}
