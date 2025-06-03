#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_erreurs.h"

FileErreurs g_file_erreurs = {NULL, NULL, 0};

int file_erreurs_enfiler(const char *nom_test, const char *nom_groupe) {
    NoeudErreur *nouveau_noeud;
    char *test_copie;
    char *groupe_copie;
    
    nouveau_noeud = malloc(sizeof(NoeudErreur));
    if (nouveau_noeud == NULL) {
        return 0;
    }
    
    test_copie = malloc(strlen(nom_test) + 1);
    groupe_copie = malloc(strlen(nom_groupe) + 1);
    
    if (test_copie == NULL || groupe_copie == NULL) {
        free(test_copie);
        free(groupe_copie);
        free(nouveau_noeud);
        return 0;
    }
    
    strcpy(test_copie, nom_test);
    strcpy(groupe_copie, nom_groupe);
    
    nouveau_noeud->erreur.nom_test = test_copie;
    nouveau_noeud->erreur.nom_groupe = groupe_copie;
    nouveau_noeud->suivant = NULL;
    
    if (g_file_erreurs.queue == NULL) {
        g_file_erreurs.tete = nouveau_noeud;
        g_file_erreurs.queue = nouveau_noeud;
    } else {
        g_file_erreurs.queue->suivant = nouveau_noeud;
        g_file_erreurs.queue = nouveau_noeud;
    }
    
    g_file_erreurs.taille++;
    return 1;
}

ErreurTest* file_erreurs_defiler(void) {
    NoeudErreur *ancien_premier;
    ErreurTest *erreur;
    
    if (g_file_erreurs.tete == NULL) {
        return NULL;
    }
    
    ancien_premier = g_file_erreurs.tete;
    erreur = &ancien_premier->erreur;
    
    g_file_erreurs.tete = ancien_premier->suivant;
    
    if (g_file_erreurs.tete == NULL) {
        g_file_erreurs.queue = NULL;
    }
    
    g_file_erreurs.taille--;
    
    return erreur;
}

ErreurTest* file_erreurs_premier(void) {
    if (g_file_erreurs.tete == NULL) {
        return NULL;
    }
    
    return &g_file_erreurs.tete->erreur;
}

int file_erreurs_vide(void) {
    return g_file_erreurs.tete == NULL;
}

int file_erreurs_taille(void) {
    return g_file_erreurs.taille;
}

void file_erreurs_liberer(void) {
    NoeudErreur *courant;
    NoeudErreur *suivant;
    
    courant = g_file_erreurs.tete;
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant->erreur.nom_test);
        free(courant->erreur.nom_groupe);
        free(courant);
        courant = suivant;
    }
    
    g_file_erreurs.tete = NULL;
    g_file_erreurs.queue = NULL;
    g_file_erreurs.taille = 0;
}

void file_erreurs_afficher(void) {
    NoeudErreur *courant;
    int index;
    
    printf("Erreurs de tests (total: %d):\n", g_file_erreurs.taille);
    
    if (g_file_erreurs.taille == 0) {
        printf(" Aucune erreur détectée.\n");
        return;
    }
    
    courant = g_file_erreurs.tete;
    index = 1;
    while (courant != NULL) {
        printf("  [%d] %s::%s - ÉCHEC\n", index,
               courant->erreur.nom_groupe,
               courant->erreur.nom_test);
        courant = courant->suivant;
        index++;
    }
}