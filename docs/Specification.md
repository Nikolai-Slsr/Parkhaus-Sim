
## Inputs: bei Programmstart per Terminal konfigurierbar
- Anzahl der Stellplätze (int oder short)
- Max. Parkdauer (für alle gültig) (int)
- Simulationsdauer (Zeitschritte) (int)
- Ankunftswahrscheinlichkeit Fahrzeuge in % (int)
- Seed für Zufallszahlen (int)
!(Abfangen von Ungültigen Eingaben beachten)!

## Aufbau Parkhaus: (struct Fahrzeug *Parkhaus[Anzahl Stellplätze] bei leer = NULL, bei belegt = *struct Fahrzeug)
- Anzahl Stellplätze (constant), zwei Zustände: leer, belegt (char, boolean)
    - Verwaltung aktuell parkender Fahrzeuge

## Aufbau Fahrzeuge: (struct) 
- persönliche ID (int oder short)
- verbleibende Parkdauer (int)
- Zeitpunkt der Einfahrt ins Parkhaus(int)
- Zeitpunkt der Ankunft (int) (Wird gebraucht, um die Wartezeit zu berechnen)
- zufällige Parkdauer (beachte max. Parkdauer) (int)

## Aufbau Warteschlange:
- Linked List mit Referenz auf first und last.
- Dynamische Speicherallokation
- Dynamische Größe
- Nodes sind eigene Structs, in dem eine Referenz auf das nächste Element und ein Fahrzeug-Struct gespeichert werden.

## Voraussetzung Parken:
- Einparken nur bei freien Stellplätzen
- bei keinen freien Stellplätzen -> Warteschlange vor dem Parkhaus (Queue) 
- Fahrzeuge verlassen Parkhaus nach Ablauf der Parkdauer oder nach max. Parkdauer

## Ausgabe:
- pro Zeitschritt min. 5 Statistiken und am Ende der Simulation
- Ausgabe per Terminal und als .txt Datei