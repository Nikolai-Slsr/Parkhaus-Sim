# Übersicht der geplanten Statistiken

## b) Geplante Statistiken (mindestens 5)

Die Parkhaus-Simulation erfasst und gibt folgende Statistiken aus, um die Auslastung zu bewerten und bauliche Erweiterungen zu planen:

### 1. **Aktuelle Belegung**
- **Beschreibung**: Anzahl der aktuell belegten Stellplätze
- **Zweck**: Zeigt die momentane Auslastung des Parkhauses
- **Format**: Absolute Zahl (z.B. "45 / 100")
- **Ausgabe**: Pro Zeitschritt

### 2. **Prozentuale Auslastung**
- **Beschreibung**: Verhältnis belegter zu gesamten Stellplätzen in Prozent
- **Zweck**: Ermöglicht schnelle Einschätzung der Kapazitätsausnutzung
- **Format**: Prozentwert (z.B. "45.0%")
- **Ausgabe**: Pro Zeitschritt und als Durchschnitt am Ende

### 3. **Warteschlangenlänge**
- **Beschreibung**: Anzahl der Fahrzeuge, die vor dem Parkhaus warten
- **Zweck**: Indikator für Kapazitätsengpässe
- **Format**: Absolute Zahl (z.B. "12 Fahrzeuge")
- **Ausgabe**: Pro Zeitschritt, Maximum am Ende

### 4. **Angekommene Fahrzeuge gesamt**
- **Beschreibung**: Kumulative Anzahl aller Fahrzeuge, die während der Simulation ankamen
- **Zweck**: Gesamtnachfrage ermitteln
- **Format**: Absolute Zahl (z.B. "1247 Fahrzeuge")
- **Ausgabe**: Pro Zeitschritt (kumulativ) und am Ende

### 5. **Geparkte Fahrzeuge gesamt**
- **Beschreibung**: Kumulative Anzahl aller Fahrzeuge, die erfolgreich geparkt haben
- **Zweck**: Erfüllte Nachfrage messen
- **Format**: Absolute Zahl (z.B. "1180 Fahrzeuge")
- **Ausgabe**: Pro Zeitschritt (kumulativ) und am Ende

### Zusätzliche Statistiken (optional, aber wertvoll):

### 6. **Maximale Belegung**
- **Beschreibung**: Höchste gleichzeitige Anzahl geparkter Fahrzeuge
- **Zweck**: Peak-Auslastung erkennen
- **Format**: Absolute Zahl
- **Ausgabe**: Am Ende der Simulation

### 7. **Maximale Warteschlangenlänge**
- **Beschreibung**: Höchste Anzahl gleichzeitig wartender Fahrzeuge
- **Zweck**: Extremsituationen identifizieren
- **Format**: Absolute Zahl
- **Ausgabe**: Am Ende der Simulation

### 8. **Durchschnittliche Belegung**
- **Beschreibung**: Mittlere Anzahl geparkter Fahrzeuge über alle Zeitschritte
- **Zweck**: Grundlastermittlung für Dimensionierung
- **Format**: Dezimalzahl
- **Ausgabe**: Am Ende der Simulation

---

## c) Format der geplanten Ausgabe

### Ausgabe pro Zeitschritt (Konsole):

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

### CSV-Dateiausgabe (parkhaus_statistik.csv):

```
Zeitschritt,Belegte_Plaetze,Gesamt_Plaetze,Auslastung_Prozent,Warteschlange,Angekommene_Gesamt,Geparkte_Gesamt
1,1,100,1.0,0,1,0
2,2,100,2.0,0,2,0
3,3,100,3.0,0,3,0
...
42,45,100,45.0,3,127,115
```

### Finale Zusammenfassung am Ende (Konsole):

```
==========================================
       SIMULATIONS-ZUSAMMENFASSUNG        
==========================================

Simulationsdauer: 1000 Zeitschritte

Stellplätze:
  Gesamtanzahl: 100
  Maximale Belegung: 98
  Durchschnittliche Belegung: 67.4
  Durchschnittliche Auslastung: 67.4%

Fahrzeuge:
  Angekommene Fahrzeuge: 2450
  Geparkte Fahrzeuge: 2380
  Noch wartende Fahrzeuge: 5

Warteschlange:
  Maximale Länge: 15
  Aktuelle Länge: 5

Empfehlungen für bauliche Erweiterung:
  - Hohe Warteschlange erkannt!
  - Empfehlung: Mindestens 7 zusätzliche Stellplätze

==========================================
```

### Beispielhafte Visualisierung (konzeptionell):

Für spätere Erweiterungen könnte die CSV-Datei genutzt werden, um Grafiken zu erstellen:

```
Auslastung über Zeit:
100% |                              ************
 90% |                   ************
 80% |          **********
 70% |    ******
 60% |****
     |________________________________________
     0    200   400   600   800   1000  Zeit

Warteschlange über Zeit:
 20  |     *
 15  |     **
 10  |    ****
  5  |  *******
  0  |*****************************************
     |________________________________________
     0    200   400   600   800   1000  Zeit
```

---

## Begründung der Statistikauswahl

Die ausgewählten Statistiken ermöglichen eine umfassende Bewertung:

1. **Auslastungsanalyse**: Belegung und prozentuale Auslastung zeigen, ob Kapazitäten gut genutzt werden

2. **Engpasserkennung**: Warteschlangenlänge identifiziert Zeiten mit Kapazitätsproblemen

3. **Nachfrageanalyse**: Angekommene vs. geparkte Fahrzeuge zeigen unerfüllte Nachfrage

4. **Dimensionierungsgrundlage**: Durchschnittswerte und Maximalwerte helfen bei der Planung von Erweiterungen

5. **Trendanalyse**: Zeitliche Entwicklung in CSV-Datei ermöglicht Mustererkennung

6. **Entscheidungsunterstützung**: Konkrete Empfehlungen basierend auf den Kennzahlen

Diese Kombination erfüllt die Anforderung von mindestens 5 Statistiken und bietet praktischen Nutzen für die Bewertung baulicher Erweiterungen.
