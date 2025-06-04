#include <stdio.h>
#include <stdlib.h>
#include "couleurs.h"
#include "tests.h"
#include "groupe_test.h"
#include "file_erreurs.h"
#include "liste_test.h"

int test_add();
int test_sub();
int test_mul();

int main() {
    GroupeTest *ari;

    ari = groupe_test_creer("Arithmetique");

    groupe_test_ajouter(ari, "Addition", test_add);
    groupe_test_ajouter(ari, "Soustraction", test_sub);
    groupe_test_ajouter(ari, "Multiplication", test_mul);

    printf("===== ALPHA TESTS =====\n\n");
    liste_tests_exe_n_print();
    printf("\n");

    printf("====================\n");
    printf("RÉSULTAT: %d/%d", liste_tests_nb_succes(), total_tests());

    if (file_erreurs_taille() > 0) {
        printf("%s KO%s\n", couleur_rouge, couleur_defaut);
        file_erreurs_afficher();
    } else {
        printf("%s OK%s\n", couleur_vert, couleur_defaut);
    }
    printf("====================\n");

    liste_tests_liberer();
    file_erreurs_liberer();

    return 0;
}
