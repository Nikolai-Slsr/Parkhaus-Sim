/**
 * @file statistik.h
 * @brief Funktionen zur Erfassung und Ausgabe von Simulationsstatistiken
 * 
 * Diese Datei enthält alle Funktionen zur Berechnung, Speicherung und
 * Ausgabe der Statistiken für die Parkhaus-Simulation.
 * 
 * @author Parkhaus-Simulation Team
 * @date 2026-02-18
 * @version 1.0
 */

#ifndef STATISTIK_H
#define STATISTIK_H

#include "parkhaus.h"
#include <stdio.h>

/**
 * @struct SimulationsStatistik
 * @brief Sammelt alle Statistikdaten während der Simulation
 * 
 * Diese Struktur speichert kumulative und aktuelle Statistiken über
 * die gesamte Simulationsdauer.
 */
typedef struct {
    /* Kumulative Statistiken */
    int gesamt_angekommene_fahrzeuge;    /**< Gesamtzahl angekommener Fahrzeuge */
    int gesamt_geparkte_fahrzeuge;       /**< Gesamtzahl erfolgreich geparkter Fahrzeuge */
    int gesamt_abgewiesene_fahrzeuge;    /**< Fahrzeuge, die nie parken konnten */
    long gesamt_parkzeit;                /**< Summe aller Parkzeiten */
    long gesamt_wartezeit;               /**< Summe aller Wartezeiten in der Warteschlange */
    
    /* Maximale Werte */
    int max_belegung;                    /**< Maximale Anzahl belegter Stellplätze */
    int max_warteschlange;               /**< Maximale Länge der Warteschlange */
    
    /* Aktuelle Werte (pro Zeitschritt) */
    int aktuelle_belegung;               /**< Aktuell belegte Stellplätze */
    int aktuelle_warteschlange;          /**< Aktuelle Länge der Warteschlange */
    int zeitschritt;                     /**< Aktueller Zeitschritt */
    
    /* Berechnete Werte */
    double durchschnittliche_belegung;   /**< Durchschnittliche Belegung über Zeit */
    double auslastung_prozent;           /**< Prozentuale Auslastung */
    
} SimulationsStatistik;

/**
 * @brief Initialisiert die Statistikstruktur
 * 
 * Setzt alle Statistikwerte auf ihre Anfangswerte (meist 0).
 * 
 * @return SimulationsStatistik Initialisierte Statistikstruktur
 * 
 * @post Alle Werte sind auf Anfangswerte gesetzt
 */
SimulationsStatistik statistik_initialisieren(void);

/**
 * @brief Aktualisiert die Statistik nach jedem Zeitschritt
 * 
 * Wird am Ende jedes Zeitschritts aufgerufen, um die aktuellen Werte
 * zu erfassen und kumulative Werte zu aktualisieren.
 * 
 * @param statistik Zeiger auf die Statistikstruktur
 * @param parkhaus Zeiger auf das Parkhaus
 * @param neue_fahrzeuge Anzahl neu angekommener Fahrzeuge in diesem Schritt
 * @param ausgefahrene Anzahl ausgefahrener Fahrzeuge in diesem Schritt
 * 
 * @pre statistik != NULL
 * @pre parkhaus != NULL
 * @post Statistikwerte sind aktualisiert
 */
void statistik_zeitschritt_aktualisieren(SimulationsStatistik* statistik,
                                          const Parkhaus* parkhaus,
                                          int neue_fahrzeuge,
                                          int ausgefahrene);

/**
 * @brief Gibt Statistiken für aktuellen Zeitschritt auf Konsole aus
 * 
 * Gibt formatiert die wichtigsten Statistiken des aktuellen Zeitschritts
 * auf der Konsole aus.
 * 
 * @param statistik Zeiger auf die Statistikstruktur
 * @param parkhaus Zeiger auf das Parkhaus
 * 
 * @pre statistik != NULL
 * @pre parkhaus != NULL
 */
void statistik_zeitschritt_ausgeben(const SimulationsStatistik* statistik,
                                     const Parkhaus* parkhaus);

/**
 * @brief Schreibt Statistiken für aktuellen Zeitschritt in Datei
 * 
 * Schreibt die Statistiken des aktuellen Zeitschritts in eine
 * Textdatei im CSV-Format für spätere Auswertung.
 * 
 * @param statistik Zeiger auf die Statistikstruktur
 * @param parkhaus Zeiger auf das Parkhaus
 * @param datei Zeiger auf geöffnete Datei
 * 
 * @pre statistik != NULL
 * @pre parkhaus != NULL
 * @pre datei != NULL und geöffnet im Schreibmodus
 */
void statistik_zeitschritt_in_datei(const SimulationsStatistik* statistik,
                                     const Parkhaus* parkhaus,
                                     FILE* datei);

/**
 * @brief Berechnet finale Statistiken am Ende der Simulation
 * 
 * Berechnet Durchschnittswerte und andere abgeleitete Statistiken
 * nach Abschluss der Simulation.
 * 
 * @param statistik Zeiger auf die Statistikstruktur
 * @param anzahl_stellplaetze Gesamtzahl der Stellplätze
 * 
 * @pre statistik != NULL
 * @pre anzahl_stellplaetze > 0
 * @post Durchschnittswerte sind berechnet
 */
void statistik_finale_berechnung(SimulationsStatistik* statistik,
                                  int anzahl_stellplaetze);

/**
 * @brief Gibt finale Zusammenfassung der Simulation aus
 * 
 * Gibt eine detaillierte Zusammenfassung aller Statistiken nach
 * Abschluss der Simulation auf der Konsole aus.
 * 
 * @param statistik Zeiger auf die Statistikstruktur
 * @param anzahl_stellplaetze Gesamtzahl der Stellplätze
 * 
 * @pre statistik != NULL
 * @pre anzahl_stellplaetze > 0
 */
void statistik_zusammenfassung_ausgeben(const SimulationsStatistik* statistik,
                                         int anzahl_stellplaetze);

/**
 * @brief Öffnet eine Statistik-Ausgabedatei
 * 
 * Erstellt eine neue Datei für die Statistikausgabe und schreibt
 * den CSV-Header.
 * 
 * @param dateiname Name der zu erstellenden Datei
 * @return FILE* Zeiger auf geöffnete Datei, NULL bei Fehler
 * 
 * @post Bei Erfolg: Datei ist geöffnet und Header ist geschrieben
 */
FILE* statistik_datei_oeffnen(const char* dateiname);

/**
 * @brief Schließt die Statistik-Ausgabedatei
 * 
 * @param datei Zeiger auf die zu schließende Datei
 * 
 * @pre datei != NULL
 * @post Datei ist geschlossen
 */
void statistik_datei_schliessen(FILE* datei);

#endif /* STATISTIK_H */
