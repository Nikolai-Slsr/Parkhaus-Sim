/**
 * @file parkhaus.h
 * @brief Hauptdatenstruktur und Verwaltungsfunktionen für das Parkhaus
 * 
 * Diese Datei enthält die Datenstruktur des Parkhauses sowie alle
 * zentralen Funktionen zur Verwaltung der Stellplätze und Fahrzeuge.
 * 
 * @author Parkhaus-Simulation Team
 * @date 2026-02-18
 * @version 1.0
 */

#ifndef PARKHAUS_H
#define PARKHAUS_H

#include "fahrzeug.h"
#include "warteschlange.h"

/**
 * @struct Parkhaus
 * @brief Repräsentiert das gesamte Parkhaus mit allen Stellplätzen
 * 
 * Diese Struktur verwaltet alle Stellplätze, die Warteschlange und
 * zusätzliche Informationen zur Simulation.
 */
typedef struct {
    Fahrzeug* stellplaetze;         /**< Array der Stellplätze (NULL = leer) */
    int anzahl_stellplaetze;        /**< Gesamtzahl der Stellplätze */
    int belegte_stellplaetze;       /**< Anzahl aktuell belegter Stellplätze */
    Warteschlange warteschlange;    /**< Warteschlange vor dem Parkhaus */
    int naechste_fahrzeug_id;       /**< Nächste zu vergebende Fahrzeug-ID */
} Parkhaus;

/**
 * @brief Initialisiert ein neues Parkhaus
 * 
 * Allokiert Speicher für die Stellplätze und initialisiert alle
 * Verwaltungsstrukturen.
 * 
 * @param anzahl_stellplaetze Anzahl der Stellplätze im Parkhaus
 * @return Parkhaus* Zeiger auf das initialisierte Parkhaus, NULL bei Fehler
 * 
 * @pre anzahl_stellplaetze > 0
 * @post Rückgabewert zeigt auf ein gültiges, leeres Parkhaus
 */
Parkhaus* parkhaus_initialisieren(int anzahl_stellplaetze);

/**
 * @brief Gibt allen vom Parkhaus allokierten Speicher frei
 * 
 * Gibt die Stellplätze, die Warteschlange und das Parkhaus selbst frei.
 * 
 * @param parkhaus Zeiger auf das Parkhaus
 * 
 * @pre parkhaus != NULL
 * @post Aller vom Parkhaus verwendeter Speicher ist freigegeben
 */
void parkhaus_freigeben(Parkhaus* parkhaus);

/**
 * @brief Versucht ein Fahrzeug im Parkhaus zu parken
 * 
 * Sucht einen freien Stellplatz und parkt das Fahrzeug dort.
 * Wenn kein Stellplatz frei ist, wird das Fahrzeug zur Warteschlange hinzugefügt.
 * 
 * @param parkhaus Zeiger auf das Parkhaus
 * @param fahrzeug Das zu parkende Fahrzeug
 * @return int 1 wenn erfolgreich geparkt, 0 wenn in Warteschlange, -1 bei Fehler
 * 
 * @pre parkhaus != NULL
 * @post Bei Erfolg: Fahrzeug ist auf einem Stellplatz oder in der Warteschlange
 */
int parkhaus_fahrzeug_einfahren(Parkhaus* parkhaus, Fahrzeug fahrzeug);

/**
 * @brief Lässt ein Fahrzeug aus dem Parkhaus ausfahren
 * 
 * Entfernt das Fahrzeug vom angegebenen Stellplatz und markiert diesen als frei.
 * 
 * @param parkhaus Zeiger auf das Parkhaus
 * @param stellplatz_index Index des Stellplatzes
 * @return Fahrzeug Das ausgefahrene Fahrzeug
 * 
 * @pre parkhaus != NULL
 * @pre 0 <= stellplatz_index < parkhaus->anzahl_stellplaetze
 * @pre Stellplatz ist belegt
 * @post Stellplatz ist frei, belegte_stellplaetze um 1 reduziert
 */
Fahrzeug parkhaus_fahrzeug_ausfahren(Parkhaus* parkhaus, int stellplatz_index);

/**
 * @brief Prüft alle Stellplätze und lässt Fahrzeuge ausfahren
 * 
 * Durchläuft alle Stellplätze, prüft die Parkdauer und lässt Fahrzeuge
 * mit abgelaufener Parkdauer ausfahren.
 * 
 * @param parkhaus Zeiger auf das Parkhaus
 * @param ausgefahrene_fahrzeuge Array zum Speichern ausgefahrener Fahrzeuge
 * @param max_groesse Maximale Größe des Arrays
 * @return int Anzahl der ausgefahrenen Fahrzeuge
 * 
 * @pre parkhaus != NULL
 * @pre ausgefahrene_fahrzeuge != NULL oder max_groesse == 0
 * @post Alle Fahrzeuge mit abgelaufener Parkdauer sind ausgefahren
 */
int parkhaus_fahrzeuge_ausfahren_lassen(Parkhaus* parkhaus, 
                                         Fahrzeug* ausgefahrene_fahrzeuge,
                                         int max_groesse);

/**
 * @brief Verarbeitet wartende Fahrzeuge aus der Warteschlange
 * 
 * Versucht Fahrzeuge aus der Warteschlange auf freie Stellplätze zu parken.
 * 
 * @param parkhaus Zeiger auf das Parkhaus
 * @return int Anzahl der eingeparkten Fahrzeuge aus der Warteschlange
 * 
 * @pre parkhaus != NULL
 * @post Alle möglichen Fahrzeuge aus Warteschlange sind geparkt
 */
int parkhaus_warteschlange_abarbeiten(Parkhaus* parkhaus);

/**
 * @brief Aktualisiert alle Parkdauern der geparkten Fahrzeuge
 * 
 * Wird in jedem Zeitschritt aufgerufen, um die Parkdauer aller Fahrzeuge
 * zu dekrementieren.
 * 
 * @param parkhaus Zeiger auf das Parkhaus
 * 
 * @pre parkhaus != NULL
 * @post Alle parkdauer-Werte sind um 1 reduziert (mindestens 0)
 */
void parkhaus_tick(Parkhaus* parkhaus);

/**
 * @brief Sucht einen freien Stellplatz
 * 
 * @param parkhaus Zeiger auf das Parkhaus
 * @return int Index des freien Stellplatzes, -1 wenn alle belegt
 * 
 * @pre parkhaus != NULL
 */
int parkhaus_finde_freien_stellplatz(const Parkhaus* parkhaus);

/**
 * @brief Prüft ob Stellplatz belegt ist
 * 
 * @param parkhaus Zeiger auf das Parkhaus
 * @param stellplatz_index Index des Stellplatzes
 * @return int 1 wenn belegt, 0 wenn frei
 * 
 * @pre parkhaus != NULL
 * @pre 0 <= stellplatz_index < parkhaus->anzahl_stellplaetze
 */
int parkhaus_ist_stellplatz_belegt(const Parkhaus* parkhaus, int stellplatz_index);

/**
 * @brief Gibt aktuelle Belegung des Parkhauses aus
 * 
 * @param parkhaus Zeiger auf das Parkhaus
 * 
 * @pre parkhaus != NULL
 */
void parkhaus_status_ausgeben(const Parkhaus* parkhaus);

#endif /* PARKHAUS_H */
