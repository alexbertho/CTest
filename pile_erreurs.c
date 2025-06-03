#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pile_erreurs.h"

PileErreurs g_pile_erreurs = {NULL, 0, 0};

static int pile_erreurs_redimensionner(void) {
    int nouvelle_capacite;
    ErreurTest *nouveaux_elements;
    
    nouvelle_capacite = g_pile_erreurs.capacite * 2;
    nouveaux_elements = realloc(g_pile_erreurs.elements, 
                                nouvelle_capacite * sizeof(ErreurTest));
    if (nouveaux_elements == NULL) {
        return 0;
    }
    g_pile_erreurs.elements = nouveaux_elements;
    g_pile_erreurs.capacite = nouvelle_capacite;
    return 1;
}

void pile_erreurs_init(int capacite_initiale) {
    g_pile_erreurs.elements = malloc(capacite_initiale * sizeof(ErreurTest));
    if (g_pile_erreurs.elements == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la pile d'erreurs.\n");
        exit(EXIT_FAILURE);
    }
    g_pile_erreurs.taille = 0;
    g_pile_erreurs.capacite = capacite_initiale;
}

int pile_erreurs_empiler(const char *nom_test, const char *nom_groupe) {
    char *test_copie;
    char *groupe_copie;
    
    if (g_pile_erreurs.taille >= g_pile_erreurs.capacite) {
        if (!pile_erreurs_redimensionner()) {
            return 0;
        }
    }
    
    test_copie = malloc(strlen(nom_test) + 1);
    groupe_copie = malloc(strlen(nom_groupe) + 1);
    
    if (test_copie == NULL || groupe_copie == NULL) {
        free(test_copie);
        free(groupe_copie);
        return 0;
    }
    
    strcpy(test_copie, nom_test);
    strcpy(groupe_copie, nom_groupe);
    
    g_pile_erreurs.elements[g_pile_erreurs.taille].nom_test = test_copie;
    g_pile_erreurs.elements[g_pile_erreurs.taille].nom_groupe = groupe_copie;
    
    g_pile_erreurs.taille++;
    return 1;
}

ErreurTest* pile_erreurs_depiler(void) {
    if (g_pile_erreurs.taille == 0) {
        return NULL;
    }
    
    g_pile_erreurs.taille--;
    return &g_pile_erreurs.elements[g_pile_erreurs.taille];
}

ErreurTest* pile_erreurs_sommet(void) {
    if (g_pile_erreurs.taille == 0) {
        return NULL;
    }
    
    return &g_pile_erreurs.elements[g_pile_erreurs.taille - 1];
}

int pile_erreurs_vide(void) {
    return g_pile_erreurs.taille == 0;
}

int pile_erreurs_taille(void) {
    return g_pile_erreurs.taille;
}

void pile_erreurs_liberer(void) {
    int i;
    
    for (i = 0; i < g_pile_erreurs.taille; i++) {
        free(g_pile_erreurs.elements[i].nom_test);
        free(g_pile_erreurs.elements[i].nom_groupe);
    }
    free(g_pile_erreurs.elements);
    g_pile_erreurs.elements = NULL;
    g_pile_erreurs.taille = 0;
    g_pile_erreurs.capacite = 0;
}

void pile_erreurs_afficher(void) {
    int i;
    
    printf("Pile d'erreurs (taille: %d):\n", g_pile_erreurs.taille);
    for (i = g_pile_erreurs.taille - 1; i >= 0; i--) {
        printf("  [%d] Test: %s, Groupe: %s\n", i, 
               g_pile_erreurs.elements[i].nom_test,
               g_pile_erreurs.elements[i].nom_groupe);
    }
}