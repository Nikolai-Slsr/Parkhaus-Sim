/**
 * @file eingabe.h
 * @brief Funktionen zur Eingabevalidierung und Konfiguration
 * 
 * Diese Datei enthält Funktionen zum Einlesen und Validieren der
 * Simulationsparameter vom Benutzer.
 * 
 * @author Parkhaus-Simulation Team
 * @date 2026-02-18
 * @version 1.0
 */

#ifndef EINGABE_H
#define EINGABE_H

/**
 * @struct SimulationsParameter
 * @brief Enthält alle konfigurierbaren Parameter der Simulation
 * 
 * Diese Struktur speichert alle vom Benutzer eingegebenen oder
 * vorgegebenen Parameter für die Simulation.
 */
typedef struct {
    int anzahl_stellplaetze;          /**< Anzahl der Stellplätze im Parkhaus */
    int max_parkdauer;                /**< Maximale Parkdauer in Zeitschritten */
    int simulationsdauer;             /**< Dauer der Simulation in Zeitschritten */
    int ankunftswahrscheinlichkeit;   /**< Wahrscheinlichkeit für Fahrzeugankunft (0-100%) */
    unsigned int random_seed;         /**< Seed für Zufallszahlengenerator */
} SimulationsParameter;

/**
 * @brief Liest alle Simulationsparameter vom Benutzer ein
 * 
 * Fordert den Benutzer zur Eingabe aller notwendigen Parameter auf
 * und validiert diese.
 * 
 * @return SimulationsParameter Die eingelesenen und validierten Parameter
 * 
 * @post Rückgabewert enthält gültige Simulationsparameter
 */
SimulationsParameter eingabe_parameter_einlesen(void);

/**
 * @brief Validiert die Anzahl der Stellplätze
 * 
 * Prüft ob die eingegebene Anzahl im gültigen Bereich liegt.
 * 
 * @param anzahl Die zu validierende Anzahl
 * @return int 1 wenn gültig, 0 sonst
 * 
 * @post Rückgabewert zeigt Gültigkeit an
 */
int eingabe_validiere_stellplaetze(int anzahl);

/**
 * @brief Validiert die maximale Parkdauer
 * 
 * @param dauer Die zu validierende Dauer
 * @return int 1 wenn gültig, 0 sonst
 */
int eingabe_validiere_parkdauer(int dauer);

/**
 * @brief Validiert die Simulationsdauer
 * 
 * @param dauer Die zu validierende Dauer
 * @return int 1 wenn gültig, 0 sonst
 */
int eingabe_validiere_simulationsdauer(int dauer);

/**
 * @brief Validiert die Ankunftswahrscheinlichkeit
 * 
 * @param wahrscheinlichkeit Die zu validierende Wahrscheinlichkeit (0-100)
 * @return int 1 wenn gültig, 0 sonst
 */
int eingabe_validiere_wahrscheinlichkeit(int wahrscheinlichkeit);

/**
 * @brief Liest eine ganze Zahl vom Benutzer ein
 * 
 * Liest eine Zeile von stdin und konvertiert sie zu einer Ganzzahl.
 * Behandelt fehlerhafte Eingaben.
 * 
 * @param wert Zeiger auf Variable für den eingelesenen Wert
 * @return int 1 bei Erfolg, 0 bei Fehler
 * 
 * @pre wert != NULL
 * @post Bei Erfolg: *wert enthält eingelesene Zahl
 */
int eingabe_lies_ganzzahl(int* wert);

/**
 * @brief Liest eine vorzeichenlose ganze Zahl vom Benutzer ein
 * 
 * @param wert Zeiger auf Variable für den eingelesenen Wert
 * @return int 1 bei Erfolg, 0 bei Fehler
 * 
 * @pre wert != NULL
 * @post Bei Erfolg: *wert enthält eingelesene Zahl
 */
int eingabe_lies_unsigned(unsigned int* wert);

/**
 * @brief Gibt die aktuellen Simulationsparameter aus
 * 
 * Zeigt eine Übersicht aller eingestellten Parameter an.
 * 
 * @param parameter Zeiger auf die Parameterstuktur
 * 
 * @pre parameter != NULL
 */
void eingabe_parameter_ausgeben(const SimulationsParameter* parameter);

#endif /* EINGABE_H */
