#include "lex.c"

int main() {
  const char *file_name1 = "test_cases/test_case1.c";
  const char *file_name2 = "test_cases/test_case2.c";
  const char *file_name3 = "test_cases/test_case3.c";

  IntArray *result_1 = initialize_int_array(1);
  IntArray *result_2 = initialize_int_array(1);
  IntArray *result_3 = initialize_int_array(1);

  IntArray *expected_1 = initialize_int_array(1);
  IntArray *expected_2 = initialize_int_array(1);
  IntArray *expected_3 = initialize_int_array(1);

  push_back(expected_1, IntKeyword);
  push_back(expected_1, Identifier);
  push_back(expected_1, OpenParen);
  push_back(expected_1, CloseParen);
  push_back(expected_1, OpenBracket);
  push_back(expected_1, ReturnKeyword);
  push_back(expected_1, IntegerLiteral);
  push_back(expected_1, Semicolon);
  push_back(expected_1, CloseBracket);

  push_back(expected_2, IntKeyword);
  push_back(expected_2, Identifier);
  push_back(expected_2, OpenParen);
  push_back(expected_2, CloseParen);
  push_back(expected_2, OpenBracket);
  push_back(expected_2, ReturnKeyword);
  push_back(expected_2, IntegerLiteral);
  push_back(expected_2, Semicolon);
  push_back(expected_2, CloseBracket);

  push_back(expected_3, IntKeyword);
  push_back(expected_3, Identifier);
  push_back(expected_3, OpenParen);
  push_back(expected_3, CloseParen);
  push_back(expected_3, OpenBracket);
  push_back(expected_3, ReturnKeyword);
  push_back(expected_3, IntegerLiteral);
  push_back(expected_3, Semicolon);
  push_back(expected_3, CloseBracket);

  lex(file_name1, result_1);
  lex(file_name2, result_2);
  lex(file_name3, result_3);

  assert(result_1->size == expected_1->size);
  assert(result_2->size == expected_2->size);
  assert(result_3->size == expected_3->size);

  for (int i = 0; i < result_1->size; ++i) {
    printf("Index %d: result_1 = %d, expected_1 = %d\n", i, result_1->array[i], expected_1->array[i]);
    assert(result_1->array[i] == expected_1->array[i]);
  }

  for (int i = 0; i < result_2->size; ++i) {
    printf("Index %d: result_2 = %d, expected_2 = %d\n", i, result_2->array[i], expected_2->array[i]);
    assert(result_2->array[i] == expected_2->array[i]);
  }

  for (int i = 0; i < result_3->size; ++i) {
    printf("Index %d: result_3 = %d, expected_3 = %d\n", i, result_3->array[i], expected_3->array[i]);
    assert(result_3->array[i] == expected_3->array[i]);
  }
} 