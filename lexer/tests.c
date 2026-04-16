#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../C_array/char_array.c"
#include "../parser/compare_strings.c"
#include "../lexer/token.c"
#include "../C_array/token_array.c"
#include "../C_map/map.c"
#include "../lexer/lex.c"
#include "../lexer/read_file.c"
#include "../codegen/write_to_file.c"

void run_test_case(char *test_case_path, char *result_file_path, char *expected_file_path) {
  TokenArray *arr = initialize_token_array(1);

  const char *src = read_file(test_case_path);

  assert(lex(src, arr));

  write_tokens_to_file(result_file_path, arr);

  const char *s1 = read_file(result_file_path);
  const char *s2 = read_file(expected_file_path);

  assert(compare(s1, s2));
}

int main() {
  run_test_case("test_cases/test_case7.c", "lexer/test1_result.txt", "lexer/test1_expected.txt");
  run_test_case("test_cases/test_case8.c", "lexer/test2_result.txt", "lexer/test2_expected.txt");
  run_test_case("test_cases/test_case9.c", "lexer/test3_result.txt", "lexer/test3_expected.txt");

  printf("All test passed succesfully");
  return 0;
}