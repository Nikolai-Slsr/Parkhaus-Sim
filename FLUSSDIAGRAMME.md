# Flussdiagramme der zentralen Funktionen

## h) Mindestens 3 zentrale Funktionen als Flussdiagramme

Diese Datei enthält Flussdiagramme für die drei wichtigsten Funktionen der Parkhaus-Simulation.

---

## 1. Flussdiagramm: `simuliere_zeitschritt()`

Dies ist die zentrale Funktion, die in jedem Zeitschritt aufgerufen wird und alle Aktionen koordiniert.

```
                        START
                          |
                          v
        ┌─────────────────────────────────────┐
        │ Initialisiere neue_fahrzeuge = 0    │
        └─────────────────┬───────────────────┘
                          │
                          v
        ┌─────────────────────────────────────┐
        │ Generiere Zufallszahl (0-99)        │
        └─────────────────┬───────────────────┘
                          │
                          v
              ┌───────────────────────┐
              │ Zufall < Ankunfts-    │
              │ wahrscheinlichkeit?   │
              └─────┬──────────┬──────┘
                NEIN│          │JA
                    │          v
                    │  ┌──────────────────────────┐
                    │  │ Erstelle neues Fahrzeug  │
                    │  │ mit eindeutiger ID       │
                    │  └──────────┬───────────────┘
                    │             │
                    │             v
                    │  ┌──────────────────────────┐
                    │  │ Erhöhe naechste_id       │
                    │  │ Erhöhe neue_fahrzeuge    │
                    │  └──────────┬───────────────┘
                    │             │
                    │             v
                    │  ┌──────────────────────────┐
                    │  │ parkhaus_fahrzeug_       │
                    │  │ einfahren(fahrzeug)      │
                    │  └──────────┬───────────────┘
                    │             │
                    │             v
                    │  ┌──────────────────────────┐
                    │  │ Ausgabe: Fahrzeug X      │
                    │  │ eingeparkt/wartend       │
                    │  └──────────┬───────────────┘
                    │             │
                    └─────────────┼───────────────┘
                                  │
                                  v
                    ┌─────────────────────────────┐
                    │ parkhaus_tick()             │
                    │ (Reduziere alle Parkdauern) │
                    └─────────────┬───────────────┘
                                  │
                                  v
                    ┌─────────────────────────────┐
                    │ parkhaus_fahrzeuge_         │
                    │ ausfahren_lassen()          │
                    └─────────────┬───────────────┘
                                  │
                                  v
                    ┌─────────────────────────────┐
                    │ Für jedes ausgefahrene      │
                    │ Fahrzeug: Ausgabe Info      │
                    └─────────────┬───────────────┘
                                  │
                                  v
                    ┌─────────────────────────────┐
                    │ parkhaus_warteschlange_     │
                    │ abarbeiten()                │
                    └─────────────┬───────────────┘
                                  │
                                  v
              ┌─────────────────────────────────┐
              │ Aus_warteschlange > 0?          │
              └──────┬──────────────┬───────────┘
                 NEIN│              │JA
                     │              v
                     │   ┌────────────────────────┐
                     │   │ Ausgabe: X Fahrzeuge   │
                     │   │ aus Warteschlange      │
                     │   └────────────┬───────────┘
                     │                │
                     └────────────────┼───────────┘
                                      │
                                      v
                    ┌─────────────────────────────┐
                    │ statistik_zeitschritt_      │
                    │ aktualisieren()             │
                    └─────────────┬───────────────┘
                                  │
                                  v
                                 END
```

**Komplexität**: Diese Funktion ist zentral, da sie:
- Fahrzeugankunft simuliert (stochastisch)
- Einpark-Logik anstößt
- Zeitfortschritt verwaltet
- Ausfahrten verarbeitet
- Warteschlange abarbeitet
- Statistiken aktualisiert

---

## 2. Flussdiagramm: `parkhaus_fahrzeug_einfahren()`

Diese Funktion versucht ein Fahrzeug zu parken oder reiht es in die Warteschlange ein.

```
                        START
                          |
                          v
        ┌─────────────────────────────────────┐
        │ Eingabe: parkhaus, fahrzeug         │
        └─────────────────┬───────────────────┘
                          │
                          v
              ┌───────────────────────┐
              │ parkhaus == NULL?     │
              └─────┬──────────┬──────┘
                 JA │          │ NEIN
                    v          │
          ┌──────────────┐    │
          │ RETURN -1    │    │
          │ (Fehler)     │    │
          └──────────────┘    │
                              │
                              v
        ┌─────────────────────────────────────┐
        │ freier_platz =                      │
        │ parkhaus_finde_freien_stellplatz()  │
        └─────────────────┬───────────────────┘
                          │
                          v
              ┌───────────────────────┐
              │ freier_platz >= 0?    │
              │ (Platz gefunden?)     │
              └─────┬──────────┬──────┘
                 NEIN│         │ JA
                     │         v
                     │  ┌─────────────────────────┐
                     │  │ parkhaus->stellplaetze  │
                     │  │ [freier_platz]=fahrzeug │
                     │  └──────────┬──────────────┘
                     │             │
                     │             v
                     │  ┌─────────────────────────┐
                     │  │ Erhöhe belegte_         │
                     │  │ stellplaetze um 1       │
                     │  └──────────┬──────────────┘
                     │             │
                     │             v
                     │  ┌─────────────────────────┐
                     │  │ RETURN 1                │
                     │  │ (Erfolgreich geparkt)   │
                     │  └─────────────────────────┘
                     │
                     v
        ┌─────────────────────────────────────┐
        │ ergebnis = warteschlange_           │
        │ hinzufuegen(&warteschlange,         │
        │             fahrzeug)               │
        └─────────────────┬───────────────────┘
                          │
                          v
              ┌───────────────────────┐
              │ ergebnis == 0?        │
              │ (Erfolgreich)         │
              └─────┬──────────┬──────┘
                 NEIN│         │ JA
                     │         v
                     │  ┌─────────────────────────┐
                     │  │ RETURN 0                │
                     │  │ (In Warteschlange)      │
                     │  └─────────────────────────┘
                     │
                     v
          ┌──────────────────────┐
          │ RETURN -1            │
          │ (Fehler bei          │
          │  Warteschlange)      │
          └──────────────────────┘
```

**Komplexität**: Diese Funktion ist wichtig, weil sie:
- Entscheidet zwischen direktem Parken und Warteschlange
- Zwei verschiedene Datenpfade verwaltet (Stellplatz vs. Queue)
- Fehlerbehandlung durchführt
- Atomare Operation für Fahrzeugaufnahme

---

## 3. Flussdiagramm: `parkhaus_fahrzeuge_ausfahren_lassen()`

Diese Funktion durchläuft alle Stellplätze und lässt Fahrzeuge mit abgelaufener Parkdauer ausfahren.

```
                        START
                          |
                          v
        ┌─────────────────────────────────────┐
        │ Eingabe: parkhaus,                  │
        │          ausgefahrene_fahrzeuge[],  │
        │          max_groesse                │
        └─────────────────┬───────────────────┘
                          │
                          v
              ┌───────────────────────┐
              │ parkhaus == NULL?     │
              └─────┬──────────┬──────┘
                 JA │          │ NEIN
                    v          │
          ┌──────────────┐    │
          │ RETURN 0     │    │
          └──────────────┘    │
                              │
                              v
        ┌─────────────────────────────────────┐
        │ Initialisiere:                      │
        │ anzahl_ausgefahren = 0              │
        │ i = 0                               │
        └─────────────────┬───────────────────┘
                          │
                          v
        ┌─────────────────────────────────────┐
        │         SCHLEIFE START              │
        └─────────────────┬───────────────────┘
                          │
                          v
              ┌───────────────────────┐
              │ i < anzahl_           │
              │ stellplaetze?         │
              └─────┬──────────┬──────┘
                 NEIN│         │ JA
                     │         v
                     │  ┌─────────────────────────┐
                     │  │ Stellplatz [i]          │
                     │  │ belegt?                 │
                     │  │ (id >= 0)               │
                     │  └──┬────────────┬─────────┘
                     │  NEIN│          │ JA
                     │     │           v
                     │     │   ┌──────────────────┐
                     │     │   │ fahrzeug_soll_   │
                     │     │   │ ausfahren()?     │
                     │     │   └───┬──────────┬───┘
                     │     │    NEIN│        │ JA
                     │     │       │         v
                     │     │       │  ┌──────────────────────────┐
                     │     │       │  │ fahrzeug = parkhaus_     │
                     │     │       │  │ fahrzeug_ausfahren(      │
                     │     │       │  │     parkhaus, i)         │
                     │     │       │  └──────────┬───────────────┘
                     │     │       │             │
                     │     │       │             v
                     │     │       │  ┌──────────────────────────┐
                     │     │       │  │ Optional: Speichere in   │
                     │     │       │  │ ausgefahrene_fahrzeuge[] │
                     │     │       │  │ falls Platz vorhanden    │
                     │     │       │  └──────────┬───────────────┘
                     │     │       │             │
                     │     │       │             v
                     │     │       │  ┌──────────────────────────┐
                     │     │       │  │ Erhöhe anzahl_           │
                     │     │       │  │ ausgefahren um 1         │
                     │     │       │  └──────────┬───────────────┘
                     │     │       │             │
                     │     └───────┴─────────────┼───────────────┘
                     │                           │
                     │             ┌─────────────┘
                     │             │
                     │             v
                     │  ┌─────────────────────────┐
                     │  │ Erhöhe i um 1           │
                     │  └──────────┬──────────────┘
                     │             │
                     └─────────────┘
                                   │
                                   v (zurück zu SCHLEIFE START)
                                   
                                   │ (NEIN von i < anzahl_stellplaetze)
                                   v
                     ┌─────────────────────────────┐
                     │ RETURN anzahl_ausgefahren   │
                     └─────────────────────────────┘
                                   │
                                   v
                                  END
```

**Komplexität**: Diese Funktion ist wichtig, weil sie:
- Über alle Stellplätze iteriert (O(n))
- Mehrere Bedingungen prüft (belegt? Parkdauer abgelaufen?)
- Fahrzeuge ausfahren lässt (Zustandsänderung)
- Optional Ergebnisse sammelt
- Zentral für Freigabe von Stellplätzen

---

## 4. Zusätzliches Flussdiagramm: `warteschlange_hinzufuegen()`

Als Bonus ein viertes Diagramm für die dynamische Speicherverwaltung:

```
                        START
                          |
                          v
        ┌─────────────────────────────────────┐
        │ Eingabe: warteschlange, fahrzeug    │
        └─────────────────┬───────────────────┘
                          │
                          v
              ┌───────────────────────┐
              │ warteschlange==NULL?  │
              └─────┬──────────┬──────┘
                 JA │          │ NEIN
                    v          │
          ┌──────────────┐    │
          │ RETURN -1    │    │
          └──────────────┘    │
                              │
                              v
        ┌─────────────────────────────────────┐
        │ neuer_knoten = malloc(              │
        │     sizeof(WarteschlangenKnoten))   │
        └─────────────────┬───────────────────┘
                          │
                          v
              ┌───────────────────────┐
              │ neuer_knoten==NULL?   │
              │ (Speicherfehler)      │
              └─────┬──────────┬──────┘
                 JA │          │ NEIN
                    v          │
    ┌────────────────────┐    │
    │ Ausgabe: Fehler    │    │
    │ RETURN -1          │    │
    └────────────────────┘    │
                              │
                              v
        ┌─────────────────────────────────────┐
        │ neuer_knoten->fahrzeug = fahrzeug   │
        │ neuer_knoten->naechster = NULL      │
        └─────────────────┬───────────────────┘
                          │
                          v
              ┌───────────────────────┐
              │ warteschlange->ende   │
              │ == NULL?              │
              │ (Warteschlange leer?) │
              └─────┬──────────┬──────┘
                 NEIN│         │ JA
                     │         v
                     │  ┌─────────────────────────┐
                     │  │ warteschlange->anfang = │
                     │  │   neuer_knoten          │
                     │  │ warteschlange->ende =   │
                     │  │   neuer_knoten          │
                     │  └──────────┬──────────────┘
                     │             │
                     v             │
        ┌─────────────────────────────────────┐
        │ warteschlange->ende->naechster =    │
        │   neuer_knoten                      │
        │ warteschlange->ende = neuer_knoten  │
        └─────────────────┬───────────────────┘
                          │
                          └──────────────┐
                                         │
                                         v
                    ┌─────────────────────────────┐
                    │ Erhöhe warteschlange->      │
                    │ anzahl um 1                 │
                    └─────────────┬───────────────┘
                                  │
                                  v
                    ┌─────────────────────────────┐
                    │ RETURN 0 (Erfolg)           │
                    └─────────────┬───────────────┘
                                  │
                                  v
                                 END
```

**Komplexität**: Diese Funktion zeigt:
- Dynamische Speicherallokation (malloc)
- Fehlerbehandlung bei Speicherproblemen
- Unterscheidung: Leere vs. nicht-leere Liste
- Korrekte Zeiger-Manipulation
- FIFO-Warteschlangen-Logik

---

## Legende für Flussdiagramme

- **Rechteck**: Prozess/Operation
- **Raute**: Entscheidung (if/else)
- **Abgerundetes Rechteck**: Start/Ende
- **Pfeile**: Kontrollfluss
- **Text an Pfeilen**: Bedingung (JA/NEIN)

---

## Anmerkungen zu den Diagrammen

### Warum diese 3 (bzw. 4) Funktionen?

1. **simuliere_zeitschritt()**: 
   - Orchestriert den gesamten Ablauf
   - Höchste Komplexität in Ablauflogik
   - Nicht main(), da main() nur Koordination ist

2. **parkhaus_fahrzeug_einfahren()**:
   - Kernfunktion der Business-Logik
   - Komplexe Entscheidungslogik
   - Interaktion zwischen mehreren Modulen

3. **parkhaus_fahrzeuge_ausfahren_lassen()**:
   - Zeigt Iteration über Datenstruktur
   - Mehrere verschachtelte Bedingungen
   - Wichtig für Ablauf der Simulation

4. **warteschlange_hinzufuegen()** (Bonus):
   - Demonstriert dynamische Speicherverwaltung
   - Zentral für technische Anforderung
   - Zeigt Pointer-Manipulation

### Alternativen die NICHT gewählt wurden:

- **main()**: Zu simpel, nur Koordination
- **fahrzeug_tick()**: Trivial (nur Dekrement)
- **eingabe_lies_ganzzahl()**: Hilfsfunktion, nicht zentral
- **statistik_ausgeben()**: Nur Ausgabe, keine Logik

---

## ASCII-Art Alternative (falls Diagramme zu groß):

Für kleinere Bildschirme hier eine kompakte Version von `parkhaus_fahrzeug_einfahren()`:

```
START → [Null-Check] → [Finde freien Platz]
           ↓ Fehler         ↓
        RETURN -1      [Platz frei?]
                          ↙    ↘
                        JA     NEIN
                        ↓        ↓
                  [Parke Auto]  [→ Warteschlange]
                        ↓             ↓
                   RETURN 1      RETURN 0/-1
```

---

## Zusammenfassung

Diese Flussdiagramme zeigen:
- ✓ Mindestens 3 zentrale Funktionen (tatsächlich 4)
- ✓ Komplexe Ablauflogik
- ✓ Entscheidungsbäume
- ✓ Schleifen und Iterationen
- ✓ Fehlerbehandlung
- ✓ Dynamische Speicherverwaltung
- ✓ Interaktion zwischen Modulen

Sie erfüllen damit die Anforderung h) aus Teil I vollständig.
