#ifndef PILE_ERREURS_H
#define PILE_ERREURS_H

#ifndef GROUPE_TEST_H
#include "groupe_test.h"
#endif

typedef struct {
    char *nom_test;
    char *nom_groupe;
} ErreurTest;

typedef struct {
    ErreurTest *elements;
    int taille;
    int capacite;
} PileErreurs;

extern PileErreurs g_pile_erreurs;

void pile_erreurs_init(int capacite_initiale);
int pile_erreurs_empiler(const char *nom_test, const char *nom_groupe);
ErreurTest* pile_erreurs_depiler(void);
ErreurTest* pile_erreurs_sommet(void);
int pile_erreurs_vide(void);
int pile_erreurs_taille(void);
void pile_erreurs_liberer(void);
void pile_erreurs_afficher(void);

#endif