#include <stdio.h>
#include "couleurs.h"

int run_test(int boolean, char *description, char* fichier, int line) {
    if (!boolean) {
        printf("\n%s[TEST ECHOUÉ]%s ", couleur_jaune, couleur_defaut);
        printf("%s ligne %d\n", fichier, line);
        printf("%s\n", description);
    }
    return boolean;
}
