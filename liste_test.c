#include <stdio.h>
#include <stdlib.h>

#include "groupe_test.h"
#include "liste_test.h"

ListeTests *liste_tests = NULL;

void liste_tests_ajouter(GroupeTest *groupe) {
    ListeTests *nouveau = malloc(sizeof(ListeTests));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la liste de tests.\n");
        exit(EXIT_FAILURE);
    }
    
    nouveau->groupe = groupe;
    nouveau->suivant = NULL;
    
    if (liste_tests == NULL) {
        liste_tests = nouveau;
    } else {
        ListeTests *courant = liste_tests->suivant;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau;
    }
}

void liste_tests_exe_n_print(void) {
    ListeTests *courant = liste_tests;
    
    while (courant != NULL) {
        if (courant->groupe != NULL) {
            groupe_test_executer(courant->groupe);
            groupe_test_afficher_resultats(courant->groupe);
        }
        courant = courant->suivant;
    }
}

int liste_tests_nb_succes(void) {
    int nb_succes = 0;
    ListeTests *courant = liste_tests;

    while (courant != NULL) {
        if (courant->groupe != NULL) {
            nb_succes += (courant->groupe->nb_tests - courant->groupe->nb_tests_echoues);
        }
        courant = courant->suivant;
    }
    
    return nb_succes;
}

int total_tests(void) {
    int total = 0;
    ListeTests *courant = liste_tests;

    while (courant != NULL) {
        if (courant->groupe != NULL) {
            total += courant->groupe->nb_tests;
        }
        courant = courant->suivant;
    }
    
    return total;
}

void liste_tests_liberer(void) {
    ListeTests *courant = liste_tests;
    ListeTests *temp;

    while (courant != NULL) {
        temp = courant;
        courant = courant->suivant;
        groupe_test_liberer(temp->groupe);
        free(temp);
    }
    
    liste_tests->groupe = NULL;
    liste_tests->suivant = NULL;
}