#include "../C_array/array.c"
#include "../C_map/map.c"
#include "read_file.c"
#include <ctype.h>

int lex(const char *file_name, IntArray *result) {
  const char *file_contents = read_file(file_name);

  if (file_contents == NULL) {
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

  while (*file_contents != '\0') {
    if (isspace(*file_contents)) {
      file_contents++;
      continue;
    }
    if (isdigit(*file_contents)) {
      while ((*file_contents) != '\0' && isdigit(*file_contents)) {
        file_contents++;
      }
      push_back(result, IntegerLiteral);
      continue;
    }
    if (isalpha(*file_contents)) {
      char word[256];
      int word_len = 0;
      while ((*file_contents) != '\0' && isalpha(*file_contents) &&
             word_len < 255) {
        word[word_len] = (*file_contents);
        word_len++;
        file_contents++;
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

    word[0] = (*file_contents);
    word[1] = '\0';

    FindRes res = StrMap_find(&char_map, word);
    if (res.found) {
      push_back(result, res.val);
    } else {
      push_back(result, Unknown);
    }
    file_contents++;
  }
  return 1;
}
