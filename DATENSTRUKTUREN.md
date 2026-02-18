# Übersicht der Datentypen und Strukturen

## d) Festgelegte Datentypen und Strukturen

Diese Datei dokumentiert alle in der Parkhaus-Simulation verwendeten Datenstrukturen mit Begründung für die Designentscheidungen.

---

## 1. Struktur: Fahrzeug (fahrzeug.h)

```c
typedef struct {
    int id;                           // Eindeutige ID des Fahrzeugs
    int parkdauer;                    // Verbleibende Parkdauer in Zeitschritten
    int einfahrtszeit;                // Zeitpunkt der Einfahrt ins Parkhaus
    int urspruengliche_parkdauer;     // Ursprünglich zugewiesene Parkdauer
} Fahrzeug;
```

### Begründung:
- **id**: Eindeutige Identifikation zur Nachverfolgung einzelner Fahrzeuge
- **parkdauer**: Countdown für automatisches Ausfahren, wird pro Zeitschritt dekrementiert
- **einfahrtszeit**: Ermöglicht Berechnung der Verweilzeit (wichtig für Statistiken)
- **urspruengliche_parkdauer**: Für Statistiken und Debugging (Vergleich mit verbleibender Zeit)
- **Einfache Struktur**: Nur primitive Datentypen, keine Zeiger → einfaches Kopieren möglich

---

## 2. Struktur: WarteschlangenKnoten (warteschlange.h)

```c
typedef struct WarteschlangenKnoten {
    Fahrzeug fahrzeug;                        // Das wartende Fahrzeug
    struct WarteschlangenKnoten* naechster;   // Zeiger auf nächsten Knoten
} WarteschlangenKnoten;
```

### Begründung:
- **Verkettete Liste**: Dynamische Größe ohne Obergrenze (Anforderung: dynamische Speicherverwaltung)
- **Selbstreferenzierende Struktur**: Ermöglicht beliebig lange Ketten
- **FIFO-Prinzip**: Realistische Warteschlange (First In, First Out)

---

## 3. Struktur: Warteschlange (warteschlange.h)

```c
typedef struct {
    WarteschlangenKnoten* anfang;   // Zeiger auf erstes Element
    WarteschlangenKnoten* ende;     // Zeiger auf letztes Element
    int anzahl;                     // Anzahl wartender Fahrzeuge
} Warteschlange;
```

### Begründung:
- **anfang-Zeiger**: Schnelles Entnehmen (O(1)) vom Anfang
- **ende-Zeiger**: Schnelles Hinzufügen (O(1)) am Ende
- **anzahl**: Vermeidung von Durchläufen zur Größenbestimmung
- **Effiziente Operationen**: Alle Basis-Operationen in konstanter Zeit

---

## 4. Struktur: Parkhaus (parkhaus.h)

```c
typedef struct {
    Fahrzeug* stellplaetze;         // Array der Stellplätze (NULL = leer)
    int anzahl_stellplaetze;        // Gesamtzahl der Stellplätze
    int belegte_stellplaetze;       // Anzahl aktuell belegter Stellplätze
    Warteschlange warteschlange;    // Warteschlange vor dem Parkhaus
    int naechste_fahrzeug_id;       // Nächste zu vergebende Fahrzeug-ID
} Parkhaus;
```

### Begründung:
- **stellplaetze als Array**: Feste Größe wie in realer Welt, direkter Zugriff auf Stellplatz i
- **Dynamische Allokation**: Größe zur Laufzeit konfigurierbar
- **belegte_stellplaetze**: Schnelle Abfrage ohne Durchlauf (O(1) statt O(n))
- **Eingebettete Warteschlange**: Logische Zusammengehörigkeit
- **ID-Generator**: Zentrale Vergabe verhindert Duplikate

---

## 5. Struktur: SimulationsParameter (eingabe.h)

```c
typedef struct {
    int anzahl_stellplaetze;          // Anzahl der Stellplätze im Parkhaus
    int max_parkdauer;                // Maximale Parkdauer in Zeitschritten
    int simulationsdauer;             // Dauer der Simulation in Zeitschritten
    int ankunftswahrscheinlichkeit;   // Wahrscheinlichkeit für Fahrzeugankunft (0-100%)
    unsigned int random_seed;         // Seed für Zufallszahlengenerator
} SimulationsParameter;
```

### Begründung:
- **Kapselung**: Alle Konfigurationsparameter in einer Struktur
- **Einfache Übergabe**: Nur ein Parameter statt fünf einzelner
- **Erweiterbar**: Neue Parameter können leicht hinzugefügt werden
- **unsigned für seed**: Seed ist immer positiv

---

## 6. Struktur: SimulationsStatistik (statistik.h)

```c
typedef struct {
    /* Kumulative Statistiken */
    int gesamt_angekommene_fahrzeuge;    // Gesamtzahl angekommener Fahrzeuge
    int gesamt_geparkte_fahrzeuge;       // Gesamtzahl erfolgreich geparkter Fahrzeuge
    int gesamt_abgewiesene_fahrzeuge;    // Fahrzeuge, die nie parken konnten
    long gesamt_parkzeit;                // Summe aller Parkzeiten
    long gesamt_wartezeit;               // Summe aller Wartezeiten
    
    /* Maximale Werte */
    int max_belegung;                    // Maximale Anzahl belegter Stellplätze
    int max_warteschlange;               // Maximale Länge der Warteschlange
    
    /* Aktuelle Werte */
    int aktuelle_belegung;               // Aktuell belegte Stellplätze
    int aktuelle_warteschlange;          // Aktuelle Länge der Warteschlange
    int zeitschritt;                     // Aktueller Zeitschritt
    
    /* Berechnete Werte */
    double durchschnittliche_belegung;   // Durchschnittliche Belegung
    double auslastung_prozent;           // Prozentuale Auslastung
} SimulationsStatistik;
```

### Begründung:
- **Trennung nach Kategorien**: Übersichtliche Gruppierung verwandter Daten
- **long für Summen**: Vermeidung von Integer-Overflow bei langen Simulationen
- **double für Durchschnitte**: Präzise Berechnungen
- **Redundanz vermieden**: Berechnete Werte nur wenn nötig gespeichert
- **Vollständige Erfassung**: Alle geforderten Statistiken abgedeckt

---

## Design-Prinzipien

### 1. **Einfachheit**
- Keine unnötig komplexen Datenstrukturen
- Klare Namensgebung (selbstdokumentierend)

### 2. **Effizienz**
- O(1) Operationen wo möglich (z.B. Warteschlange hinzufügen/entnehmen)
- Redundante Zähler zur Vermeidung teurer Berechnungen

### 3. **Speicherverwaltung**
- Dynamische Allokation wo gefordert (Warteschlange)
- Statische Arrays wo sinnvoll (Stellplätze)
- Klare Ownership-Semantik

### 4. **Erweiterbarkeit**
- Strukturen können um Felder ergänzt werden
- Keine festen Array-Größen im Code (Konstanten verwenden)

### 5. **C-Idiomatik**
- Verwendung von typedefs für Strukturen
- Zeiger für große Strukturen, Werte für kleine
- Konventionelle Namensgebung (snake_case für Funktionen)

---

## Speicherlayout-Überlegungen

### Stellplätze als Array vs. verkettete Liste:
**Entscheidung: Array**
- **Pro Array**: 
  - Direkter Zugriff O(1)
  - Cache-freundlich (zusammenhängender Speicher)
  - Feste Größe passt zur Realität
- **Contra verkettete Liste**: 
  - Unnötiger Overhead
  - Keine Notwendigkeit für dynamisches Wachstum

### Warteschlange als Array vs. verkettete Liste:
**Entscheidung: Verkettete Liste**
- **Pro verkettete Liste**:
  - Anforderung: dynamische Speicherverwaltung
  - Unbegrenzte Länge möglich
  - Keine Reallokation nötig
- **Contra Array**:
  - Begrenzte Größe oder teure Reallokation
  - Verschwendung bei Überdimensionierung

---

## Zusammenfassung

Die gewählten Datenstrukturen:
1. ✓ Erfüllen alle funktionalen Anforderungen
2. ✓ Implementieren geforderte dynamische Speicherverwaltung
3. ✓ Ermöglichen effiziente Operationen
4. ✓ Sind wartbar und erweiterbar
5. ✓ Folgen C-Konventionen und idiomatischem Stil
