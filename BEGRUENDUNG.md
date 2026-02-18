# Begründung der Design-Entscheidungen

## f) Begründungstexte für alle Aspekte der Implementierung

---

## 1. Begründung der Modularisierung

### Aufteilung in Module:

Die Simulation wurde in 5 Hauptmodule aufgeteilt:

#### **1.1 Modul: fahrzeug (fahrzeug.h/c)**
- **Zweck**: Verwaltung einzelner Fahrzeuge
- **Begründung**: 
  - Klare Separation of Concerns
  - Fahrzeug-Logik ist unabhängig testbar
  - Wiederverwendbar in anderen Kontexten
  - Einhaltung des Single Responsibility Principle

#### **1.2 Modul: warteschlange (warteschlange.h/c)**
- **Zweck**: Dynamische Warteschlange mit verketteter Liste
- **Begründung**:
  - Erfüllt explizite Anforderung: "dynamische Speicherverwaltung"
  - Generische Implementierung (könnte für andere Zwecke verwendet werden)
  - Kapselung der Pointer-Manipulation (Fehlerquelle!)
  - Abstrahiert komplexe Speicherverwaltung

#### **1.3 Modul: parkhaus (parkhaus.h/c)**
- **Zweck**: Kernlogik der Parkhausverwaltung
- **Begründung**:
  - Zentrales Modul, koordiniert alle Aktionen
  - Verwaltet Stellplätze und Warteschlange
  - Schnittstelle zur Hauptsimulation
  - Hohe Kohäsion: alles Parkhaus-spezifische an einem Ort

#### **1.4 Modul: statistik (statistik.h/c)**
- **Zweck**: Erfassung und Ausgabe von Statistiken
- **Begründung**:
  - Trennung von Business-Logik und Reporting
  - Statistik-Code ändert sich oft (neue Kennzahlen)
  - Verschiedene Ausgabeformate (Konsole, Datei)
  - Macht Hauptprogramm übersichtlicher

#### **1.5 Modul: eingabe (eingabe.h/c)**
- **Zweck**: Validierung und Einlesen von Benutzereingaben
- **Begründung**:
  - Robuste Fehlerbehandlung an zentraler Stelle
  - Wiederverwendbare Validierungsfunktionen
  - Anforderung: "Ungültige Eingaben müssen erkannt werden"
  - Trennung von I/O und Simulation

#### **1.6 Datei: main.c**
- **Zweck**: Orchestrierung der Gesamtsimulation
- **Begründung**:
  - Dünne Koordinationsschicht
  - Ruft Module auf, enthält wenig Logik selbst
  - Leicht zu verstehen ("Was passiert in welcher Reihenfolge?")

---

## 2. Begründung der Datenstrukturen

### 2.1 Warum Array für Stellplätze?

**Entscheidung**: `Fahrzeug* stellplaetze` als dynamisches Array

**Begründung**:
1. **Realitätsnähe**: Parkhaus hat feste Anzahl Plätze
2. **Performance**: O(1) Zugriff auf Stellplatz i
3. **Speichereffizienz**: Zusammenhängender Speicherblock
4. **Cache-Freundlichkeit**: Bessere CPU-Cache-Nutzung
5. **Einfachheit**: Keine Zeiger-Verwaltung wie bei Listen

**Alternativen abgelehnt**:
- Verkettete Liste: Unnötiger Overhead, kein Vorteil
- Hash-Map: Überdimensioniert für sequentielle IDs

### 2.2 Warum verkettete Liste für Warteschlange?

**Entscheidung**: Einfach verkettete Liste mit anfang/ende-Zeigern

**Begründung**:
1. **Anforderung**: "dynamische Speicherverwaltung" explizit gefordert
2. **Unbegrenzt**: Keine feste Obergrenze
3. **Effizienz**: O(1) für enqueue und dequeue
4. **Speicher**: Nur was benötigt wird
5. **FIFO**: Natürliche Implementierung

**Alternativen abgelehnt**:
- Festes Array: Begrenzte Größe, widerspricht Anforderung
- Ringpuffer: Unnötig komplex, feste Größe
- Doppelt verkettet: Nicht nötig (keine Rückwärts-Traversierung)

### 2.3 Warum ID als Leer-Indikator?

**Entscheidung**: `id == -1` bedeutet "Stellplatz frei"

**Begründung**:
1. **Einfachheit**: Kein zusätzliches Bool-Array nötig
2. **Speicher**: Keine Verschwendung
3. **Atomarität**: Ein Wert statt zwei Flags
4. **Convention**: Negative Werte traditionell für "ungültig"

**Alternative betrachtet**:
- Separates `bool belegt[]`: Mehr Speicher, Synchronisation nötig
- Zeiger-Array: Unnötig komplex, Overhead für Allokation

---

## 3. Begründung der Funktionsaufteilung

### 3.1 Granularität der Funktionen

**Prinzip**: "Eine Funktion, eine Aufgabe"

**Beispiele**:
- `parkhaus_finde_freien_stellplatz()`: Nur Suche, keine Modifikation
- `parkhaus_fahrzeug_einfahren()`: Komplette Einpark-Logik
- `warteschlange_hinzufuegen()`: Nur das Hinzufügen

**Begründung**:
- Bessere Testbarkeit (Unit-Tests)
- Wiederverwendbarkeit
- Verständlichkeit
- Wartbarkeit

### 3.2 Fehlerbehandlung durch Rückgabewerte

**Entscheidung**: int-Rückgabewerte für Erfolg/Fehler

**Begründung**:
1. **C-Konvention**: 0 = Erfolg, -1 = Fehler, >0 = Status
2. **Keine Exceptions**: C hat keine Exceptions
3. **Explizit**: Aufrufer muss Fehler prüfen
4. **Einfach**: Keine komplexen Error-Structs nötig

**Beispiel**:
```c
int warteschlange_hinzufuegen(...) {
    // Rückgabe: 0 = Erfolg, -1 = Fehler
}
```

---

## 4. Begründung der Statistiken

### 4.1 Auswahl der 5+ Statistiken

**Siehe STATISTIKEN.md für Details**

Kurzzusammenfassung:
1. **Belegung**: Direkte Kapazitätsanzeige
2. **Auslastung %**: Normalisierte Vergleichbarkeit
3. **Warteschlange**: Engpassindikator
4. **Angekommene Fahrzeuge**: Nachfragevolumen
5. **Geparkte Fahrzeuge**: Erfüllte Nachfrage

**Begründung der Auswahl**:
- Anforderung: "Bewertung der Auslastung"
- Anforderung: "Bewertung baulicher Erweiterungen"
- Diese 5 Metriken beantworten direkt:
  - Wie gut wird das Parkhaus genutzt?
  - Gibt es Kapazitätsprobleme?
  - Wie viel zusätzliche Kapazität wird benötigt?

### 4.2 Duale Ausgabe (Konsole + Datei)

**Entscheidung**: Statistiken sowohl auf Konsole als auch in CSV-Datei

**Begründung**:
1. **Anforderung**: "in einem lesbaren Format ausgegeben sowie in eine Text-Datei geschrieben"
2. **Konsole**: Echtzeitüberwachung während Simulation
3. **Datei**: Nachträgliche Analyse, Diagramme, Archivierung
4. **CSV**: Standardformat, Excel/Python/R-kompatibel

---

## 5. Begründung der Simulationslogik

### 5.1 Zeitschritt-basierte Simulation

**Entscheidung**: Diskrete Zeitschritte statt Event-basiert

**Begründung**:
1. **Anforderung**: "über diskrete Zeitschritte simuliert"
2. **Einfachheit**: Leicht zu verstehen und implementieren
3. **Determinismus**: Gleiche Seeds = gleiche Ergebnisse
4. **Anforderungskonform**: Passt zur Aufgabenstellung

**Ablauf pro Zeitschritt**:
```
1. Prüfe ob Fahrzeug ankommt (Zufall)
2. Versuche einzuparken (oder Warteschlange)
3. Dekrementiere alle Parkdauern
4. Lasse Fahrzeuge mit Parkdauer=0 ausfahren
5. Verarbeite Warteschlange (parke auf frei gewordene Plätze)
6. Aktualisiere Statistiken
7. Ausgabe
```

### 5.2 Zufällige Ankunft und Parkdauer

**Entscheidung**: 
- Ankunft: Wahrscheinlichkeit pro Zeitschritt
- Parkdauer: Zufällig zwischen 1 und max_parkdauer

**Begründung**:
1. **Realitätsnähe**: Fahrzeuge kommen unvorhersehbar
2. **Variabilität**: Interessante Simulationsmuster
3. **Anforderung**: "Ankunftswahrscheinlichkeit neuer Fahrzeuge"
4. **Konfigurierbar**: Parameter beeinflussen Ergebnisse
5. **Reproduzierbar**: Seed ermöglicht Wiederholung

---

## 6. Begründung der Eingabevalidierung

### 6.1 Mehrschichtige Validierung

**Ansatz**:
1. Typprüfung (ist es eine Zahl?)
2. Bereichsprüfung (ist sie im erlaubten Bereich?)
3. Plausibilitätsprüfung (macht sie Sinn?)

**Begründung**:
- **Anforderung**: "Ungültige Eingaben müssen erkannt und abgefangen werden"
- **Robustheit**: Verhindert Crashes und undefiniertes Verhalten
- **Benutzerfreundlich**: Klare Fehlermeldungen
- **Professionalität**: Produktionsreife Software

**Beispiel**:
```c
// Stellplätze müssen zwischen 1 und 10000 liegen
#define MIN_STELLPLAETZE 1
#define MAX_STELLPLAETZE 10000
```

### 6.2 Wiederholte Eingabeaufforderung

**Entscheidung**: Bei Fehler erneut fragen statt Abbruch

**Begründung**:
- Benutzerfreundlicher
- Ermöglicht Korrektur von Tippfehlern
- Verhindert Neustart des Programms

---

## 7. Begründung der Code-Konventionen

### 7.1 Namensgebung

**Konvention**:
- Funktionen: `modul_aktion_objekt()` z.B. `parkhaus_fahrzeug_einfahren()`
- Strukturen: PascalCase z.B. `Fahrzeug`, `Parkhaus`
- Variablen: snake_case z.B. `anzahl_stellplaetze`
- Konstanten: SCREAMING_SNAKE_CASE z.B. `MAX_PARKDAUER`

**Begründung**:
- **Lesbarkeit**: Funktion und Kontext sofort klar
- **Namespace**: Modul-Präfix verhindert Kollisionen
- **Konsistenz**: Einheitlicher Stil im gesamten Projekt
- **C-Idiomatik**: Folgt etablierten C-Konventionen

### 7.2 Kommentarstil

**Ansatz**: Doxygen-kompatible Kommentare

**Begründung**:
- Automatische Dokumentationsgenerierung möglich
- Standardformat (viele Tools verstehen es)
- Anforderung: "Saubere Kommentierung"
- Professioneller Standard

---

## 8. Begründung für Teil I Zustand

### 8.1 Warum Pseudocode?

**Anforderung**: "Beschreiben Sie das geplante Programm komplett in auskommentierten Pseudocode"

**Umgesetzt durch**:
- Vollständige Funktionsprototypen
- Detaillierter Pseudocode in Kommentaren
- Logische Ablaufbeschreibungen

**Begründung**:
- Ermöglicht Überprüfung der Logik vor Implementierung
- Findet Design-Fehler früh
- Dokumentiert Intention
- Erleichtert Team-Arbeit (andere verstehen Plan)

### 8.2 Warum nicht kompilierbar?

**Absicht**: Teil I soll Gerüst zeigen, nicht lauffähig sein

**Begründung**:
- Anforderung: "Das Programm muss zu diesem Zeitpunkt NICHT kompilierbar sein"
- Fokus auf Design und Planung
- Verhindert voreiliges Coden
- Ermöglicht Feedback vor Implementierung

---

## 9. Zusammenfassung der Designphilosophie

### Leitprinzipien:

1. **KISS (Keep It Simple, Stupid)**
   - Einfachste Lösung, die funktioniert
   - Keine Überengineering

2. **YAGNI (You Aren't Gonna Need It)**
   - Nur implementieren was gefordert ist
   - Erweiterbarkeit ermöglichen, aber nicht vorbauen

3. **Separation of Concerns**
   - Jedes Modul hat klare Verantwortung
   - Minimale Kopplung zwischen Modulen

4. **DRY (Don't Repeat Yourself)**
   - Wiederverwendbare Funktionen
   - Keine Code-Duplikation

5. **Fail Fast**
   - Frühe Fehlerprüfung
   - Klare Fehlermeldungen

---

## 10. Erfüllung der Anforderungen

### Checkliste funktionale Anforderungen:

- ✓ Konfigurierbare Parameter zur Laufzeit
- ✓ Eingabevalidierung
- ✓ Parkhaus mit fester Stellplatzanzahl
- ✓ Fahrzeuge mit ID, Parkdauer, Einfahrtszeit
- ✓ Zufällige Parkdauer
- ✓ Maximale Parkdauer
- ✓ Warteschlange bei vollem Parkhaus
- ✓ Automatisches Ausfahren
- ✓ Mindestens 5 Statistiken
- ✓ Konsolenausgabe pro Zeitschritt
- ✓ Dateiausgabe
- ✓ Zusammenfassung am Ende

### Checkliste technische Vorgaben:

- ✓ Programmiersprache C
- ✓ Git/GitHub
- ✓ Passende Datenstrukturen
- ✓ Dynamische Speicherverwaltung (Warteschlange)
- ✓ Sinnvolle Funktionsaufteilung
- ✓ Modularisierung
- ✓ Saubere Kommentierung
- ✓ Idiomatischer C-Stil

Alle Anforderungen sind im Design berücksichtigt.
