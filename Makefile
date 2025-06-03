CC = gcc
CFLAGS = -std=c89 -g -Wall -Wextra -pedantic -Iinclude
RELEASE_CFLAGS = -O2 -DNDEBUG
DEBUG_CFLAGS = -g3 -DDEBUG -O0

BUILD_RELEASE_DIR = build/release
BUILD_DEBUG_DIR = build/debug

SRC_FILES = $(wildcard src/*/*.c src/*.c)
RELEASE_OBJ_FILES = $(patsubst src/%.c,$(BUILD_RELEASE_DIR)/%.o,$(SRC_FILES))
DEBUG_OBJ_FILES = $(patsubst src/%.c,$(BUILD_DEBUG_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(RELEASE_OBJ_FILES:.o=.d) $(DEBUG_OBJ_FILES:.o=.d)

RELEASE_BIN = bin/ctest
DEBUG_BIN = bin/ctest-debug

.PHONY: all clean debug release

# Default target
all: release

release: $(RELEASE_BIN)

debug: $(DEBUG_BIN)

$(RELEASE_BIN): $(RELEASE_OBJ_FILES) | bin
	$(CC) $(CFLAGS) $(RELEASE_CFLAGS) $^ -o $@

$(DEBUG_BIN): $(DEBUG_OBJ_FILES) | bin
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) $^ -o $@

$(BUILD_RELEASE_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(RELEASE_CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DEBUG_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) -MMD -MP -c $< -o $@

bin:
	mkdir -p bin

clean:
	rm -rf build bin

# Include dependency files (if they exist)
-include $(DEP_FILES)