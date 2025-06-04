CC = gcc
CFLAGS = -std=c89 -g -Wall -Wextra -pedantic -Iinclude
RELEASE_CFLAGS = -O2 -DNDEBUG
DEBUG_CFLAGS = -g3 -DDEBUG -O0

# Dossiers
SRC_DIR = src
INCLUDE_DIR = include
EXAMPLES_DIR = examples
BUILD_DIR = build
BIN_DIR = bin

# Sources du framework (sans main_test.c qui est un point d'entrée)
FRAMEWORK_SRC = $(filter-out $(SRC_DIR)/main_test.c, $(wildcard $(SRC_DIR)/*.c))

# Détection automatique des exemples disponibles
AVAILABLE_EXAMPLES = $(notdir $(wildcard $(EXAMPLES_DIR)/*))

# Variables par défaut
BUILD_TYPE ?= debug

# Sélection des flags selon le type de build
ifeq ($(BUILD_TYPE),release)
    CURRENT_CFLAGS = $(CFLAGS) $(RELEASE_CFLAGS)
else
    CURRENT_CFLAGS = $(CFLAGS) $(DEBUG_CFLAGS)
endif

.PHONY: all clean help list $(AVAILABLE_EXAMPLES)

# Cible par défaut
all: help

# Aide
help:
	@echo "=== CTEST Framework ==="
	@echo "Exemples disponibles:"
	@for example in $(AVAILABLE_EXAMPLES); do \
		echo "  make $$example"; \
	done
	@echo ""
	@echo "Autres cibles:"
	@echo "  make list          - Liste les exemples"
	@echo "  make clean         - Nettoie tout"
	@echo "  make clean-EXAMPLE - Nettoie un exemple"
	@echo ""
	@echo "Options:"
	@echo "  BUILD_TYPE=release - Compilation optimisée"
	@echo "  BUILD_TYPE=debug   - Compilation debug (défaut)"

# Liste des exemples
list:
	@echo "Exemples disponibles: $(AVAILABLE_EXAMPLES)"

# Génération automatique des cibles pour chaque exemple
$(AVAILABLE_EXAMPLES): %: $(BIN_DIR)/%
	@echo "Exemple '$@' compilé avec succès: $(BIN_DIR)/$@"
	@echo "  Lancer avec: ./$(BIN_DIR)/$@"

# Définition des objets par exemple (calculé dynamiquement)
define EXAMPLE_RULES
$(1)_FRAMEWORK_OBJS = $$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/$(1)/framework/%.o,$$(FRAMEWORK_SRC))
$(1)_EXAMPLE_SRCS = $$(wildcard $(EXAMPLES_DIR)/$(1)/*.c)
$(1)_EXAMPLE_OBJS = $$(patsubst $(EXAMPLES_DIR)/$(1)/%.c,$(BUILD_DIR)/$(1)/example/%.o,$$($(1)_EXAMPLE_SRCS))

# Règle pour l'exécutable de cet exemple
$(BIN_DIR)/$(1): $$($(1)_FRAMEWORK_OBJS) $$($(1)_EXAMPLE_OBJS) | $(BIN_DIR)
	@echo "Linking $(1)..."
	$(CC) $(CURRENT_CFLAGS) $$^ -o $$@

# Règles pour les objets du framework pour cet exemple
$(BUILD_DIR)/$(1)/framework/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)/$(1)/framework
	@echo "Compiling framework: $$< -> $$@"
	$(CC) $(CURRENT_CFLAGS) -c $$< -o $$@

# Règles pour les objets de l'exemple
$(BUILD_DIR)/$(1)/example/%.o: $(EXAMPLES_DIR)/$(1)/%.c | $(BUILD_DIR)/$(1)/example
	@echo "Compiling example: $$< -> $$@"
	$(CC) $(CURRENT_CFLAGS) -I$(EXAMPLES_DIR)/$(1) -c $$< -o $$@

# Création des dossiers pour cet exemple
$(BUILD_DIR)/$(1)/framework:
	@mkdir -p $$@

$(BUILD_DIR)/$(1)/example:
	@mkdir -p $$@
endef

# Génération des règles pour tous les exemples
$(foreach example,$(AVAILABLE_EXAMPLES),$(eval $(call EXAMPLE_RULES,$(example))))

# Création du dossier bin
$(BIN_DIR):
	@mkdir -p $@

# Nettoyage complet
clean:
	@echo "Nettoyage complet..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

# Nettoyage d'un exemple spécifique
clean-%:
	@echo "Nettoyage de l'exemple $*..."
	@rm -rf $(BUILD_DIR)/$* $(BIN_DIR)/$*

# Cible pour lancer un exemple après compilation
run-%: %
	@echo "Lancement de l'exemple $*:"
	@./$(BIN_DIR)/$*

# Cible pour compiler tous les exemples
all-examples: $(AVAILABLE_EXAMPLES)
	@echo "Tous les exemples compilés avec succès!"

# Debug: affiche les variables
debug-vars:
	@echo "AVAILABLE_EXAMPLES = $(AVAILABLE_EXAMPLES)"
	@echo "FRAMEWORK_SRC = $(FRAMEWORK_SRC)"
	@echo "CURRENT_CFLAGS = $(CURRENT_CFLAGS)"
	@echo "BUILD_TYPE = $(BUILD_TYPE)"

# Debug: affiche les variables pour un exemple spécifique
debug-example-%:
	@echo "=== Debug pour l'exemple $* ==="
	@echo "$*_FRAMEWORK_OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/$*/framework/%.o,$(FRAMEWORK_SRC))"
	@echo "$*_EXAMPLE_SRCS = $(wildcard $(EXAMPLES_DIR)/$*/*.c)"
	@echo "$*_EXAMPLE_OBJS = $(patsubst $(EXAMPLES_DIR)/$*/%.c,$(BUILD_DIR)/$*/example/%.o,$(wildcard $(EXAMPLES_DIR)/$*/*.c))"

# Vérification qu'un exemple existe avant compilation
check-example-%:
	@if [ ! -d "$(EXAMPLES_DIR)/$*" ]; then \
		echo "Erreur: L'exemple '$*' n'existe pas dans $(EXAMPLES_DIR)/"; \
		echo "Exemples disponibles: $(AVAILABLE_EXAMPLES)"; \
		exit 1; \
	fi
