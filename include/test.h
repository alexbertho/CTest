#ifndef TEST_H
#define TEST_H

int run_test(int boolean, char *description, char* fichier, int line);
#define RUN_TEST(BOOL) run_test(BOOL, #BOOL, __FILE__, __LINE__)

typedef struct {
    char *nom;
    int (*f)(void);
    int resultat;
} Test;

typedef struct {
    char *nom;
    Test *tests;
    int nb_tests;
} GroupeTest;

#endif