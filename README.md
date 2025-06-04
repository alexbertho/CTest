# CTest

Framework de tests unitaires léger pour C (compatible C89).

## API

### Macros de test
```c
RUN_TEST(condition)          // Teste une condition
```

### Gestion des groupes
```c
GroupeTest* groupe_test_creer(const char *nom);
int groupe_test_ajouter(GroupeTest *groupe, const char *nom_test, int (*fonction_test)(void));
void groupe_test_liberer(GroupeTest *groupe);
```

### Exécution et résultats
```c
void liste_tests_exe_n_print(void);     // Exécute et affiche tous les tests
int liste_tests_nb_succes(void);        // Nombre de tests réussis  
int total_tests(void);                   // Nombre total de tests
void liste_tests_liberer(void);         // Libère la mémoire
```

### Gestion des erreurs
```c
int file_erreurs_taille(void);          // Nombre d'erreurs
void file_erreurs_afficher(void);       // Affiche les erreurs
void file_erreurs_liberer(void);        // Libère les erreurs
```

## Utilisation du Makefile

### Lister les exemples disponibles
```bash
make help
make list
```

### Compiler un exemple
```bash
make alpha          # Compile examples/alpha/
make gold           # Compile examples/gold/
```

### Lancer un exemple
```bash
make run-alpha      # Compile et lance l'exemple alpha
./bin/alpha         # Lance directement
```

### Ajouter un nouvel exemple
1. Créer le dossier : `mkdir examples/beta`
2. Ajouter vos fichiers .c dans le dossier
3. Compiler : `make beta`

### Nettoyage
```bash
make clean          # Nettoie tout
make clean-alpha    # Nettoie un exemple spécifique
```

### Options de compilation
```bash
BUILD_TYPE=release make alpha    # Version optimisée
BUILD_TYPE=debug make alpha      # Version debug (défaut)
```

## Exemple de test

```c
#include "test.h"
#include "groupe_test.h"
#include "liste_test.h"
#include "file_erreurs.h"
#include "couleurs.h"

int test_addition() {
    int b = 1;
    b = RUN_TEST(add(2, 3) == 5) && b;
    b = RUN_TEST(add(0, 0) == 0) && b;
    return b;
}

int main() {
    GroupeTest *math = groupe_test_creer("Math");
    groupe_test_ajouter(math, "Addition", test_addition);
    
    liste_tests_exe_n_print();
    
    printf("RÉSULTAT: %d/%d", liste_tests_nb_succes(), total_tests());
    if (file_erreurs_taille() > 0) {
        printf("%s KO%s\n", couleur_rouge, couleur_defaut);
        file_erreurs_afficher();
    } else {
        printf("%s OK%s\n", couleur_vert, couleur_defaut);
    }
    
    liste_tests_liberer();
    file_erreurs_liberer();
    return 0;
}
```