CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC_DIR = src
OBJ_DIR = obj

# Die Dateien, die wir fuer Main brauchen
MAIN_OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/queue.o $(OBJ_DIR)/parkhaus.o $(OBJ_DIR)/statistics.o $(OBJ_DIR)/sim_parameters.o

# Die Dateien, die wir fuer Tests brauchen
TEST_OBJS = $(OBJ_DIR)/functions_test_file.o $(OBJ_DIR)/queue.o $(OBJ_DIR)/parkhaus.o $(OBJ_DIR)/statistics.o $(OBJ_DIR)/sim_parameters.o

# Ziel-Dateien
MAIN_TARGET = main
TEST_TARGET = functions_test

.PHONY: all clean run-test run-main

all: $(MAIN_TARGET) $(TEST_TARGET)

# Kompiliere das Hauptprogramm
$(MAIN_TARGET): $(OBJ_DIR) $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJS)

# Kompiliere die Funktionstests
$(TEST_TARGET): $(OBJ_DIR) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

# Regel zum Erzeugen der .o Dateien im obj Verzeichnis
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Erstelle den obj Ordner
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Hilfsbefehle zum schnellen Ausfuhren
run-main: $(MAIN_TARGET)
	./$(MAIN_TARGET)

run-test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Aufraeumen
clean:
	rm -rf $(OBJ_DIR) $(MAIN_TARGET) $(TEST_TARGET) Makefile_test
