#include <stdio.h>
#include <stdlib.h>
#include "couleurs.h"
#include "tests.h"

#include "groupe_test.h"
#include "file_erreurs.h"
#include "liste_test.h"

#define stop_on_error 0

void print_tests() {
    int nb_succes = liste_tests_nb_succes();
    int total = total_tests();

    printf("===== VALISP TESTS =====\n\n");
    liste_tests_exe_n_print();
    printf("\n");

    printf("====================\n");
    printf("RÉSULTAT: %d/%d", nb_succes, total);

    if (file_erreurs_taille() > 0) {
        printf("%s KO%s\n", couleur_rouge, couleur_defaut);
        file_erreurs_afficher();
    } else {
        printf("%s OK%s\n", couleur_vert, couleur_defaut);
    }
    printf("====================\n");
}

void free_all() {
    liste_tests_liberer();
    file_erreurs_liberer();
}

int main() {
    GroupeTest *ari;

    ari = groupe_test_creer("Arimetique");

    groupe_test_ajouter(ari, "Addition", test_add);
    groupe_test_ajouter(ari, "Soustraction", test_sub);
    groupe_test_ajouter(ari, "Multiplication", test_mul);

    print_tests();
    free_all();

    return 0;
}