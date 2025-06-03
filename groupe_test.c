#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "groupe_test.h"
#include "pile_erreurs.h"
#include "liste_test.h"
#include "couleurs.h"

GroupeTest* groupe_test_creer(const char *nom, int capacite_initiale) {
    GroupeTest *groupe;
    
    groupe = malloc(sizeof(GroupeTest));
    if (groupe == NULL) {
        return NULL;
    }
    
    groupe->nom = malloc(strlen(nom) + 1);
    if (groupe->nom == NULL) {
        free(groupe);
        return NULL;
    }
    strcpy(groupe->nom, nom);
    
    groupe->tests = malloc(capacite_initiale * sizeof(Test));
    if (groupe->tests == NULL) {
        free(groupe->nom);
        free(groupe);
        return NULL;
    }
    
    groupe->nb_tests = 0;
    groupe->capacite = capacite_initiale;
    groupe->nb_tests_echoues = 0;
    groupe->executed = 0;

    liste_tests_ajouter(groupe);
    
    return groupe;
}

static int groupe_test_redimensionner(GroupeTest *groupe) {
    int nouvelle_capacite;
    Test *nouveaux_tests;
    
    nouvelle_capacite = groupe->capacite * 2;
    nouveaux_tests = realloc(groupe->tests, nouvelle_capacite * sizeof(Test));
    if (nouveaux_tests == NULL) {
        return 0;
    }
    
    groupe->tests = nouveaux_tests;
    groupe->capacite = nouvelle_capacite;
    return 1;
}

int groupe_test_ajouter(GroupeTest *groupe, const char *nom_test, int (*fonction_test)(void)) {
    char *nom_copie;
    
    if (groupe == NULL || nom_test == NULL || fonction_test == NULL) {
        return 0;
    }
    
    if (groupe->nb_tests >= groupe->capacite) {
        if (!groupe_test_redimensionner(groupe)) {
            return 0;
        }
    }
    
    nom_copie = malloc(strlen(nom_test) + 1);
    if (nom_copie == NULL) {
        return 0;
    }
    strcpy(nom_copie, nom_test);
    
    groupe->tests[groupe->nb_tests].nom = nom_copie;
    groupe->tests[groupe->nb_tests].f = fonction_test;
    groupe->tests[groupe->nb_tests].resultat = 0;
    
    groupe->nb_tests++;
    return 1;
}

void groupe_test_executer(GroupeTest *groupe) {
    int i;
    
    if (groupe == NULL) {
        return;
    }

    for (i = 0; i < groupe->nb_tests; i++) {
        groupe->tests[i].resultat = groupe->tests[i].f();
        if (!groupe->tests[i].resultat) {
            pile_erreurs_empiler(groupe->tests[i].nom, groupe->nom);
            groupe->nb_tests_echoues++;
        }
    }
    groupe->executed = 1;
}

void groupe_test_afficher_resultats(GroupeTest *groupe) {
    if (groupe == NULL) {
        return;
    }

    if (!groupe->executed) {
        printf("Le groupe de tests '%s' n'a pas été exécuté.\n", groupe->nom);
        return;
    }

    printf("> %s [%d/%d] ", groupe->nom, 
           groupe->nb_tests - groupe->nb_tests_echoues, 
           groupe->nb_tests);
    if (groupe->nb_tests_echoues > 0) {
        printf("%sKO%s\n", couleur_rouge, couleur_defaut);
    } else {
        printf("%sOK%s\n", couleur_vert, couleur_defaut);
    }
}

int groupe_test_nb_echecs(GroupeTest *groupe) {
    int i;
    int nb_echecs;
    
    if (groupe == NULL) {
        return 0;
    }
    
    nb_echecs = 0;
    for (i = 0; i < groupe->nb_tests; i++) {
        if (!groupe->tests[i].resultat) {
            nb_echecs++;
        }
    }
    
    return nb_echecs;
}

int groupe_test_nb_succes(GroupeTest *groupe) {
    int i;
    int nb_succes;
    
    if (groupe == NULL) {
        return 0;
    }
    
    nb_succes = 0;
    for (i = 0; i < groupe->nb_tests; i++) {
        if (groupe->tests[i].resultat) {
            nb_succes++;
        }
    }
    
    return nb_succes;
}

void groupe_test_liberer(GroupeTest *groupe) {
    int i;
    
    if (groupe == NULL) {
        return;
    }
    
    for (i = 0; i < groupe->nb_tests; i++) {
        free(groupe->tests[i].nom);
    }
    
    free(groupe->tests);
    free(groupe->nom);
    free(groupe);
}