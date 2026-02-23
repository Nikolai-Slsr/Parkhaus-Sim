# Datentypen

## Parkhaus
Das Parkhaus soll mit einem Array von Pointern auf Fahrzeug-Structs implementiert werden, das zum Start des Programms mit der maximalen Anzahl an Stellplätzen mit NULL-Pointern initialisiert wird.
Ein NULL-Pointer repräsentiert einen leeren Stellplatz und ein Fahrzeug-Pointer einen belegten. (Fahrzeug wird im Nachfolgenden definiert)

- struct Fahrzeug *Parkhaus[Anzahl Stellplätze] - bei leer = NULL, bei belegt = *struct Fahrzeug
## Warteschlange
Die Warteschlange wird mit Hilfe einer verketteten Liste implementiert.
 Da aber mit einer normalen verketteten Liste das Einfügen an der letzten Stelle nur in O(n) möglich wäre,
 soll neben dem Pointer auf das erste Element auch ein Pointer auf das letzte Element gespeichert werden. So kann ein neues Auto auch in O(1) hinzugefügt werden.
### Die Nodes
Die Nodes sind Structs mit folgendem Aufbau:
Node:
- nextNode (node Pointer)
- aktuelles_auto (fahrzeug Pointer)

Die verkettete Liste wird in einem extra C File implementiert.
## Fahrzeug
Die Fahrzeuge werden mit einem Struct repräsentiert, welches nach folgendem Schema aufgebaut ist:
- persönliche ID (int) 
- verbleibende Parkdauer (int)
- Zeitpunkt der Einfahrt (int) 
- zufällige Parkdauer (beachte max. Parkdauer) (int)


Da die Zeitschritte diskret sind, können auch alle Variablen, die einen Zeitpunkt oder eine Zeit speichern, mit Ganzzahlen repräsentiert werden -> int
## Weitere Variablen
