#ifndef GROUPE_TEST_H
#define GROUPE_TEST_H

typedef struct {
    char *nom;
    int (*f)(void);
    int resultat;
} Test;

typedef struct {
    char *nom;
    Test *tests;
    int nb_tests;
    int nb_tests_echoues;
    int executed;
    int capacite;
} GroupeTest;

GroupeTest* groupe_test_creer(const char *nom, int capacite_initiale);
int groupe_test_ajouter(GroupeTest *groupe, const char *nom_test, int (*fonction_test)(void));
void groupe_test_executer(GroupeTest *groupe);
void groupe_test_afficher_resultats(GroupeTest *groupe);
int groupe_test_nb_echecs(GroupeTest *groupe);
int groupe_test_nb_succes(GroupeTest *groupe);
void groupe_test_liberer(GroupeTest *groupe);

#endif