#ifndef LISTE_TEST_H
#define LISTE_TEST_H

typedef struct liste_tests {
    GroupeTest *groupe;
    struct liste_tests *suivant;
} ListeTests;


void liste_tests_ajouter(GroupeTest *groupe);
void liste_tests_exe_n_print(void);
void liste_tests_liberer(void);
int liste_tests_nb_succes(void);
int total_tests(void);

extern ListeTests *liste_tests;

#endif 