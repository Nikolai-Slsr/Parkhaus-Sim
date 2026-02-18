/**
 * @file warteschlange.h
 * @brief Dynamische Warteschlange für Fahrzeuge vor dem Parkhaus
 * 
 * Diese Datei implementiert eine dynamische Warteschlange mittels verketteter Liste
 * für Fahrzeuge, die auf einen freien Stellplatz warten.
 * 
 * @author Parkhaus-Simulation Team
 * @date 2026-02-18
 * @version 1.0
 */

#ifndef WARTESCHLANGE_H
#define WARTESCHLANGE_H

#include "fahrzeug.h"

/**
 * @struct WarteschlangenKnoten
 * @brief Ein Knoten in der verketteten Warteschlange
 * 
 * Jeder Knoten enthält ein Fahrzeug und einen Zeiger auf den nächsten Knoten.
 */
typedef struct WarteschlangenKnoten {
    Fahrzeug fahrzeug;                        /**< Das wartende Fahrzeug */
    struct WarteschlangenKnoten* naechster;   /**< Zeiger auf nächsten Knoten */
} WarteschlangenKnoten;

/**
 * @struct Warteschlange
 * @brief Verwaltungsstruktur für die Warteschlange
 * 
 * Speichert Zeiger auf Anfang und Ende der Warteschlange sowie die Anzahl
 * der wartenden Fahrzeuge.
 */
typedef struct {
    WarteschlangenKnoten* anfang;   /**< Zeiger auf erstes Element */
    WarteschlangenKnoten* ende;     /**< Zeiger auf letztes Element */
    int anzahl;                     /**< Anzahl wartender Fahrzeuge */
} Warteschlange;

/**
 * @brief Initialisiert eine neue Warteschlange
 * 
 * Erstellt eine leere Warteschlange mit allen Zeigern auf NULL und Anzahl 0.
 * 
 * @return Warteschlange Neu initialisierte Warteschlange
 * 
 * @post Rückgabewert ist eine leere Warteschlange
 */
Warteschlange warteschlange_initialisieren(void);

/**
 * @brief Fügt ein Fahrzeug am Ende der Warteschlange hinzu
 * 
 * Allokiert dynamisch Speicher für einen neuen Knoten und fügt das
 * Fahrzeug am Ende der Warteschlange ein (FIFO-Prinzip).
 * 
 * @param warteschlange Zeiger auf die Warteschlange
 * @param fahrzeug Das hinzuzufügende Fahrzeug
 * @return int 0 bei Erfolg, -1 bei Speicherallokierungsfehler
 * 
 * @pre warteschlange != NULL
 * @post Bei Erfolg: warteschlange->anzahl ist um 1 erhöht
 */
int warteschlange_hinzufuegen(Warteschlange* warteschlange, Fahrzeug fahrzeug);

/**
 * @brief Entfernt und gibt das erste Fahrzeug der Warteschlange zurück
 * 
 * Entfernt das vorderste Fahrzeug aus der Warteschlange und gibt es zurück.
 * Der allokierte Speicher des Knotens wird freigegeben.
 * 
 * @param warteschlange Zeiger auf die Warteschlange
 * @param fahrzeug Zeiger auf Fahrzeug-Variable für Rückgabewert
 * @return int 0 bei Erfolg, -1 wenn Warteschlange leer
 * 
 * @pre warteschlange != NULL
 * @pre fahrzeug != NULL
 * @post Bei Erfolg: warteschlange->anzahl ist um 1 verringert
 */
int warteschlange_entnehmen(Warteschlange* warteschlange, Fahrzeug* fahrzeug);

/**
 * @brief Prüft, ob die Warteschlange leer ist
 * 
 * @param warteschlange Zeiger auf die Warteschlange
 * @return int 1 wenn leer, 0 sonst
 * 
 * @pre warteschlange != NULL
 */
int warteschlange_ist_leer(const Warteschlange* warteschlange);

/**
 * @brief Gibt die Anzahl wartender Fahrzeuge zurück
 * 
 * @param warteschlange Zeiger auf die Warteschlange
 * @return int Anzahl der Fahrzeuge in der Warteschlange
 * 
 * @pre warteschlange != NULL
 */
int warteschlange_groesse(const Warteschlange* warteschlange);

/**
 * @brief Gibt allen Speicher der Warteschlange frei
 * 
 * Durchläuft die gesamte Warteschlange und gibt den Speicher aller
 * Knoten frei. Wichtig für ordnungsgemäße Speicherverwaltung.
 * 
 * @param warteschlange Zeiger auf die Warteschlange
 * 
 * @pre warteschlange != NULL
 * @post Alle Knoten sind freigegeben, warteschlange->anzahl == 0
 */
void warteschlange_freigeben(Warteschlange* warteschlange);

/**
 * @brief Gibt den Inhalt der Warteschlange aus
 * 
 * @param warteschlange Zeiger auf die Warteschlange
 * 
 * @pre warteschlange != NULL
 */
void warteschlange_ausgeben(const Warteschlange* warteschlange);

#endif /* WARTESCHLANGE_H */
