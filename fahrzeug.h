/**
 * @file fahrzeug.h
 * @brief Datenstrukturen und Funktionen für Fahrzeugverwaltung
 * 
 * Diese Datei enthält die Definitionen für Fahrzeuge in der Parkhaus-Simulation.
 * Jedes Fahrzeug hat eine eindeutige ID, eine Parkdauer und einen Einfahrtszeitpunkt.
 * 
 * @author Parkhaus-Simulation Team
 * @date 2026-02-18
 * @version 1.0
 */

#ifndef FAHRZEUG_H
#define FAHRZEUG_H

/**
 * @struct Fahrzeug
 * @brief Repräsentiert ein Fahrzeug im Parkhaus
 * 
 * Diese Struktur speichert alle relevanten Informationen über ein Fahrzeug,
 * das im Parkhaus parkt oder in der Warteschlange steht.
 */
typedef struct {
    int id;                    /**< Eindeutige ID des Fahrzeugs */
    int parkdauer;             /**< Verbleibende Parkdauer in Zeitschritten */
    int einfahrtszeit;         /**< Zeitpunkt der Einfahrt ins Parkhaus */
    int urspruengliche_parkdauer; /**< Ursprünglich zugewiesene Parkdauer */
} Fahrzeug;

/**
 * @brief Erstellt ein neues Fahrzeug
 * 
 * Erzeugt ein neues Fahrzeug mit einer eindeutigen ID, zufälliger Parkdauer
 * und dem aktuellen Zeitschritt als Einfahrtszeit.
 * 
 * @param id Eindeutige ID für das Fahrzeug
 * @param aktuelle_zeit Aktueller Simulationszeitschritt
 * @param max_parkdauer Maximale erlaubte Parkdauer
 * @return Fahrzeug Neu erstelltes Fahrzeug
 * 
 * @pre id >= 0
 * @pre aktuelle_zeit >= 0
 * @pre max_parkdauer > 0
 * @post Rückgabewert ist ein gültiges Fahrzeug mit parkdauer <= max_parkdauer
 */
Fahrzeug fahrzeug_erstellen(int id, int aktuelle_zeit, int max_parkdauer);

/**
 * @brief Reduziert die verbleibende Parkdauer eines Fahrzeugs
 * 
 * Verringert die Parkdauer um einen Zeitschritt. Wird für jedes parkende
 * Fahrzeug pro Simulationsschritt aufgerufen.
 * 
 * @param fahrzeug Zeiger auf das Fahrzeug
 * 
 * @pre fahrzeug != NULL
 * @post fahrzeug->parkdauer ist um 1 verringert (mindestens 0)
 */
void fahrzeug_tick(Fahrzeug* fahrzeug);

/**
 * @brief Prüft, ob ein Fahrzeug ausfahren muss
 * 
 * @param fahrzeug Zeiger auf das Fahrzeug
 * @return int 1 wenn Parkdauer abgelaufen, 0 sonst
 * 
 * @pre fahrzeug != NULL
 */
int fahrzeug_soll_ausfahren(const Fahrzeug* fahrzeug);

/**
 * @brief Gibt Informationen über ein Fahrzeug aus
 * 
 * @param fahrzeug Zeiger auf das Fahrzeug
 * 
 * @pre fahrzeug != NULL
 */
void fahrzeug_ausgeben(const Fahrzeug* fahrzeug);

#endif /* FAHRZEUG_H */
