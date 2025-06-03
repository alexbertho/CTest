# Variables
CC = gcc
CFLAGS = -std=c89 -g -Wall -Wextra -pedantic
TARGET = programme
SOURCES = *.c

# Règle principale
all: $(TARGET)

# Compilation
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Nettoyage
clean:
	rm -f $(TARGET)

# Recompiler
re: clean all

# Exécuter
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean re run