#include "stoi.c"
#include <assert.h>
#include <stdio.h>

int main() {
    char *test1 = "1000";
    char *test2 = "29";
    char *test3 = "33334";
    char *test4 = "1";
    char *test5 = "0";

    printf("%d\n", stoi(test1));

    assert(1000 == stoi(test1));

    printf("%d\n", stoi(test2));

    assert(29 == stoi(test2));

    printf("%d\n", stoi(test3));

    assert(33334 == stoi(test3));

    printf("%d\n", stoi(test4));

    assert(1 == stoi(test4));

    printf("%d\n", stoi(test5));

    assert(0 == stoi(test5));
}