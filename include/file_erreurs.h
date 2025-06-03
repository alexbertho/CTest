#ifndef FILE_ERREURS_H
#define FILE_ERREURS_H

typedef struct {
    char *nom_test;
    char *nom_groupe;
} ErreurTest;

typedef struct NoeudErreur {
    ErreurTest erreur;
    struct NoeudErreur *suivant;
} NoeudErreur;

typedef struct {
    NoeudErreur *tete;
    NoeudErreur *queue;
    int taille;
} FileErreurs;

extern FileErreurs g_file_erreurs;

void file_erreurs_init(void);
int file_erreurs_enfiler(const char *nom_test, const char *nom_groupe);
ErreurTest* file_erreurs_defiler(void);
ErreurTest* file_erreurs_premier(void);
int file_erreurs_vide(void);
int file_erreurs_taille(void);
void file_erreurs_liberer(void);
void file_erreurs_afficher(void);

#endif