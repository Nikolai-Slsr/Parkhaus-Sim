# Compiler und Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -g
LDFLAGS = 

# Quell- und Objektdateien
SOURCES = main.c parkhaus.c fahrzeug.c warteschlange.c statistik.c eingabe.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = parkhaus.h fahrzeug.h warteschlange.h statistik.h eingabe.h

# Name des ausführbaren Programms
TARGET = parkhaus_simulation

# Standard-Ziel
all: $(TARGET)

# Linke das Programm
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

# Kompiliere Objektdateien
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Aufräumen
clean:
	rm -f $(OBJECTS) $(TARGET) parkhaus_statistik.csv

# Sehr gründliches Aufräumen
distclean: clean
	rm -f *~ *.bak

# Hilfe
help:
	@echo "Verfügbare Ziele:"
	@echo "  all (default) - Kompiliert das Programm"
	@echo "  clean         - Entfernt Objektdateien und ausführbares Programm"
	@echo "  distclean     - Wie clean, plus Backup-Dateien"
	@echo "  help          - Zeigt diese Hilfe an"
	@echo ""
	@echo "Hinweis: Dies ist Teil I - das Programm ist noch nicht vollständig"
	@echo "         implementiert und wird noch nicht erfolgreich kompilieren."

# Phony Targets (keine echten Dateien)
.PHONY: all clean distclean help
