# Datentypen

## Parkhaus
Das Parkhaus soll mit einem Array von Pontern auf fahrzeug Structs implementiert werden, dass zum Start des Programms in mit der Maximalenanzahl an Stellplätens mit Null Pintern initialisiert wird.
Ein NULL Pointer repesentiert ein leeren Stellplatz und ein Fahrzeuge Pointer einen Belegten. (Fahrzeuge wird im Nachfolgenden Deginiert)

- parkhaus[] (fahrzeug Pointer)
## Warteschlange
Die Warteschlange wird mit hilfe einer Verkettenen Liste implementiert, da aber mit einer normalen Verketteten Liste das Einfügen an der Letzten Stelle nur in O(n) möglich wäre soll neben dem Pointer auf das erste Element auch ein Pointer auf das Letzte Element gespeichert werden so kann ein neues Auto auch in O(1) hinzugefügt werden.

### Die Nodes
Die Nodes sind Structs mit folgendem Aufbau:
Node:
- nextNode (node Pointer)
- aktuelles_auto (fahrzeug Pointer)

Die Verkettet List wird in einem extra C File implementiert.
## Fahrzeug
Die Fahrzeuge werden mit einem Struct representiert, welches nach folgendem Schema aufgebaut ist:
- persönliche ID (int) 
- verbleibende Parkdauer (int)
- Zeitpunkt der Einfahrt (int) 
- zufällige Parkdauer (beachte max. Parkdauer) (int)


Da die Zeitschritte diskret sind, können auch alle Variablen, die einen Zeitpunkt oder eine Zeit speichern, mit Ganzzahlen repräsentiert werden -> int
## Weitere Variablen
