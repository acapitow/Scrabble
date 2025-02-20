# Nom de l'exécutable
TARGET = output/scrabble.exe

# Répertoires
SRC_DIR = src
OBJ_DIR = output

# Fichiers sources et objets
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Options du compilateur
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Compilation principale
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

# Compilation des fichiers .c en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
