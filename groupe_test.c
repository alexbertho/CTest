#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "groupe_test.h"
#include "file_erreurs.h"
#include "liste_test.h"
#include "couleurs.h"

GroupeTest* groupe_test_creer(const char *nom) {
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
    
    groupe->tests = NULL;
    groupe->nb_tests = 0;
    groupe->nb_tests_echoues = 0;
    groupe->executed = 0;

    liste_tests_ajouter(groupe);
    
    return groupe;
}

int groupe_test_ajouter(GroupeTest *groupe, const char *nom_test, int (*fonction_test)(void)) {
    NoeudTest *nouveau_noeud;
    NoeudTest *courant;
    char *nom_copie;
    
    if (groupe == NULL || nom_test == NULL || fonction_test == NULL) {
        return 0;
    }
    
    nouveau_noeud = malloc(sizeof(NoeudTest));
    if (nouveau_noeud == NULL) {
        return 0;
    }
    
    nom_copie = malloc(strlen(nom_test) + 1);
    if (nom_copie == NULL) {
        free(nouveau_noeud);
        return 0;
    }
    strcpy(nom_copie, nom_test);
    
    nouveau_noeud->test.nom = nom_copie;
    nouveau_noeud->test.f = fonction_test;
    nouveau_noeud->test.resultat = 0;
    nouveau_noeud->suivant = NULL;
    
    if (groupe->tests == NULL) {
        groupe->tests = nouveau_noeud;
    } else {
        courant = groupe->tests;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau_noeud;
    }
    
    groupe->nb_tests++;
    return 1;
}

void groupe_test_executer(GroupeTest *groupe) {
    NoeudTest *courant;
    
    if (groupe == NULL) {
        return;
    }

    courant = groupe->tests;
    while (courant != NULL) {
        courant->test.resultat = courant->test.f();
        if (!courant->test.resultat) {
            file_erreurs_enfiler(courant->test.nom, groupe->nom);
            groupe->nb_tests_echoues++;
        }
        courant = courant->suivant;
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
    NoeudTest *courant;
    int nb_echecs;
    
    if (groupe == NULL) {
        return 0;
    }
    
    nb_echecs = 0;
    courant = groupe->tests;
    while (courant != NULL) {
        if (!courant->test.resultat) {
            nb_echecs++;
        }
        courant = courant->suivant;
    }
    
    return nb_echecs;
}

int groupe_test_nb_succes(GroupeTest *groupe) {
    NoeudTest *courant;
    int nb_succes;
    
    if (groupe == NULL) {
        return 0;
    }
    
    nb_succes = 0;
    courant = groupe->tests;
    while (courant != NULL) {
        if (courant->test.resultat) {
            nb_succes++;
        }
        courant = courant->suivant;
    }
    
    return nb_succes;
}

void groupe_test_liberer(GroupeTest *groupe) {
    NoeudTest *courant;
    NoeudTest *suivant;
    
    if (groupe == NULL) {
        return;
    }
    
    courant = groupe->tests;
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant->test.nom);
        free(courant);
        courant = suivant;
    }
    
    free(groupe->nom);
    free(groupe);
}