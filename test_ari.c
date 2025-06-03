#include "ari.h"
#include "test.h"
#include <stdio.h>

int test_add() {
    int b = 1;

    b = RUN_TEST(add(1, 1) == 2) && b;
    b = RUN_TEST(add(2, 2) == 4) && b;

    b = RUN_TEST(add(3, 3) == 6) && b;
    b = RUN_TEST(add(4, 4) == 8) && b;

    return 1;
}

int test_sub() {
    int b = 1;

    b = RUN_TEST(sub(1, 1) == 0) && b;
    b = RUN_TEST(sub(2, 2) == 0) && b;

    b = RUN_TEST(sub(3, 3) == 0) && b;
    b = RUN_TEST(sub(4, 4) == 0) && b;

    return 1;
}

int test_mul() {
    int b = 1;

    b = RUN_TEST(mul(1, 1) == 1) && b;
    b = RUN_TEST(mul(2, 2) == 4) && b;

    b = RUN_TEST(mul(3, 3) == 9) && b;
    b = RUN_TEST(mul(4, 4) == 16) && b;

    return 1;
}