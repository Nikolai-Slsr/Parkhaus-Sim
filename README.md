# Parkhaus-Simulation "Rauenegg"

Programmentwurf für Programmieren 1 - Teil I  
DHBW Ravensburg

## Überblick

Dies ist die Parkhaus-Simulation "Rauenegg" - ein Programm zur Bewertung der Auslastung und möglicher baulicher Erweiterungen eines Parkhauses.

Die Simulation arbeitet mit diskreten Zeitschritten: Fahrzeuge kommen an, parken für eine bestimmte Dauer und verlassen das Parkhaus. Bei voller Auslastung warten Fahrzeuge in einer Warteschlange.

## Status: Teil I (Planungsphase)

**Wichtig**: Dies ist die Abgabe für Teil I. Das Programm ist noch nicht vollständig implementiert und kompiliert aktuell nicht. Es zeigt das geplante Grundgerüst mit:

- ✓ Vollständigen Funktionsprototypen
- ✓ Detailliertem Pseudocode
- ✓ Datenstruktur-Definitionen
- ✓ Dokumentation der Designentscheidungen

## Projektstruktur

```
Parkhaus-Sim/
├── README.md                 # Diese Datei
├── Makefile                  # Build-System (für später)
│
├── main.c                    # Hauptprogramm mit Simulationsschleife
├── parkhaus.h / parkhaus.c   # Parkhausverwaltung
├── fahrzeug.h / fahrzeug.c   # Fahrzeugverwaltung
├── warteschlange.h / .c      # Dynamische Warteschlange
├── statistik.h / statistik.c # Statistikerfassung und -ausgabe
├── eingabe.h / eingabe.c     # Eingabevalidierung
│
├── STATISTIKEN.md            # Übersicht geplante Statistiken + Ausgabeformat
├── DATENSTRUKTUREN.md        # Dokumentation der Datenstrukturen
├── BEGRUENDUNG.md            # Begründungstexte für Design-Entscheidungen
└── FLUSSDIAGRAMME.md         # Flussdiagramme der 3+ zentralen Funktionen
```

## Funktionale Anforderungen

Das Programm erfüllt folgende Anforderungen:

### Konfiguration
- Alle Parameter zur Laufzeit über Terminal konfigurierbar:
  - Anzahl Stellplätze
  - Maximale Parkdauer
  - Simulationsdauer (Zeitschritte)
  - Ankunftswahrscheinlichkeit (0-100%)
  - Random Seed (für Reproduzierbarkeit)
- Eingabevalidierung für alle Parameter

### Simulation
- Parkhaus mit fester Stellplatzanzahl
- Fahrzeuge mit eindeutiger ID, Parkdauer und Einfahrtszeit
- Zufällige Parkdauer (1 bis max_parkdauer)
- Einparken nur bei freien Stellplätzen
- Warteschlange bei vollem Parkhaus (dynamische Speicherverwaltung)
- Automatisches Ausfahren nach Ablauf der Parkdauer

### Statistiken
Mindestens 5 Statistiken pro Zeitschritt und am Ende:
1. Aktuelle Belegung
2. Prozentuale Auslastung
3. Warteschlangenlänge
4. Angekommene Fahrzeuge gesamt
5. Geparkte Fahrzeuge gesamt
6. Plus: Maximale Belegung, maximale Warteschlange, Durchschnittswerte

### Ausgabe
- Konsolenausgabe pro Zeitschritt in lesbarem Format
- CSV-Datei für spätere Auswertung
- Zusammenfassung mit Empfehlungen am Ende

## Technische Umsetzung

### Modularisierung

Das Programm ist in 5 Module aufgeteilt:

1. **fahrzeug**: Verwaltung einzelner Fahrzeuge
2. **warteschlange**: Dynamische Warteschlange (verkettete Liste)
3. **parkhaus**: Kernlogik der Parkhausverwaltung
4. **statistik**: Erfassung und Ausgabe von Statistiken
5. **eingabe**: Validierung und Einlesen von Parametern

### Datenstrukturen

- `Fahrzeug`: ID, Parkdauer, Einfahrtszeit
- `WarteschlangenKnoten`: Verkettete Liste für wartende Fahrzeuge
- `Warteschlange`: Verwaltung mit anfang/ende-Zeigern
- `Parkhaus`: Array von Stellplätzen + Warteschlange
- `SimulationsParameter`: Alle Konfigurationsparameter
- `SimulationsStatistik`: Alle erfassten Statistiken

Details siehe [DATENSTRUKTUREN.md](DATENSTRUKTUREN.md)

### Algorithmus

Pro Zeitschritt:
1. Prüfe auf Fahrzeugankunft (stochastisch)
2. Versuche Fahrzeug einzuparken (oder Warteschlange)
3. Reduziere Parkdauer aller parkenden Fahrzeuge
4. Lasse Fahrzeuge mit abgelaufener Parkdauer ausfahren
5. Verarbeite Warteschlange (parke auf freie Plätze)
6. Aktualisiere und gebe Statistiken aus

Details siehe Pseudocode in [main.c](main.c)

## Dokumentation

### Abgabeumfang Teil I

- **a)** ✓ Erste Quellcode- und Header-Dateien (*.c, *.h)
- **b) & c)** ✓ Übersicht geplante Statistiken + Ausgabeformat → [STATISTIKEN.md](STATISTIKEN.md)
- **d)** ✓ Übersicht Datentypen und Strukturen → [DATENSTRUKTUREN.md](DATENSTRUKTUREN.md)
- **e)** ✓ Funktionsprototypen mit einheitlichem Header (in *.h Dateien)
- **f)** ✓ Begründungstexte → [BEGRUENDUNG.md](BEGRUENDUNG.md)
- **g)** ✓ Pseudocode in allen Quellcode-Dateien (in Kommentaren)
- **h)** ✓ Flussdiagramme für 3+ zentrale Funktionen → [FLUSSDIAGRAMME.md](FLUSSDIAGRAMME.md)

### Code-Dokumentation

Alle Funktionen sind mit Doxygen-kompatiblen Kommentaren dokumentiert:
- Beschreibung der Funktion
- Parameter (@param)
- Rückgabewert (@return)
- Vorbedingungen (@pre)
- Nachbedingungen (@post)
- Detaillierter Pseudocode

## Kompilierung (zukünftig)

Hinweis: Das Programm ist aktuell NICHT kompilierbar (Teil I Anforderung).

Für Teil II wird folgendes möglich sein:

```bash
# Kompilieren
make

# Ausführen
./parkhaus_simulation

# Aufräumen
make clean
```

## Verwendung (geplant für Teil II)

```bash
./parkhaus_simulation
```

Das Programm fordert dann zur Eingabe der Parameter auf:
- Anzahl Stellplätze (1-10000)
- Maximale Parkdauer (1-1000 Zeitschritte)
- Simulationsdauer (1-100000 Zeitschritte)
- Ankunftswahrscheinlichkeit (0-100%)
- Random Seed (beliebige positive Zahl)

Die Simulation läuft dann und gibt pro Zeitschritt Statistiken aus.
Am Ende erfolgt eine Zusammenfassung mit Empfehlungen.

Ergebnisse werden in `parkhaus_statistik.csv` gespeichert.

## Beispiel-Ausgabe (geplant)

```
==========================================
Zeitschritt: 42
==========================================
Belegte Stellplätze: 45 / 100
Auslastung: 45.0%
Warteschlange: 3 Fahrzeuge
Angekommene Fahrzeuge gesamt: 127
Geparkte Fahrzeuge gesamt: 115
==========================================
```

Details siehe [STATISTIKEN.md](STATISTIKEN.md)

## Entwickler

Parkhaus-Simulation Team  
DHBW Ravensburg, 2026

## Lizenz

Studienarbeit - DHBW Ravensburg

---

**Abgabetermin Teil I**: 03.03.2026, 23:59 Uhr (CET)  
**Kontakt bei Fragen**: braunagel@dhbw-ravensburg.de 
