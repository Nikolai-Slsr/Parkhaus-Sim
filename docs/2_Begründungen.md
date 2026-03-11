# Begründungen und Erklärungen für unser Projekt

## 1.0 Lösung der Aufgabenstellung
>Wie haben wir die Aufgabenstellung gelöst?

### 1.1 Aufgabenteil 1
Bevor wir beginnen konnten, wirklich autonom zu arbeiten, haben wir Folgendes noch in Zusammenarbeit erledigt:
- Gemeinsam einen Gesamtplan erstellt.
- Alle Issues im GitHub Repo gesammelt um einen Überblick zu bekommen.
- Ein grundlegendes Flowchart für main erstellt, das alle grundlegenden Funktionen und Logiken des Programms beinhaltet.
- Die grundlegende Modulstruktur mit Parkhaus, Queue und Statistik festgelegt.
- Dann haben wir aufgeteilt, dass Nikolai Schlosser die Queue, Julius Faustmann das Parkhaus und Esther Birngruber die Statistiken macht
Somit konnte jeder von uns mit dem Pseudocode und seiner Header Datei starten.

Für die schnelle Kommunikation haben wir auch eine WhatsApp Gruppe erstellt und uns ggf darüber informiert und Fragen gestellt.
Wir haben darauf geachtet, dass jeder Merge-Request von mindestens einer anderen Person (bei wichtigen Merges auch von beiden) reviewed und erst dann gemerged wurde.
Wenn wir zusammen an Funktionen und Issues gearbeitet haben, haben wir das Größtenteils in den commit messages dazu geschrieben.

Während der Arbeit an unseren Header-Dateien fiel uns auf, dass uns einiges strukturell noch fehlt, wie z.B:
- sim_parameters.h und sim_parameters.c : um die eingegebenen Simulationsparameter mehrmals zu nutzen, haben wir das Lesen und speichern dieser Parameter in einer eigenen Datei ausgelagert
- vehicle.h : da wir die Informationen von den Fahrzeugen in mehreren Funktionen und Header-Dateien nutzen, haben wir diesen struct auch ausgelagert.
### 1.2 Aufgabenteil 2

Unsere Arbeitsweise im zweiten Teil der Aufgabe lief deutlich einfacher, da wir schon einen vollständigen Plan und guten Pseudocode hatten.
Da wir die verschiedenen Teile des Programms gut aufgeteilt hatten, konnten wir queue.c, parkhaus.c, sim_parameters.c und statistics.c gut in Einzelarbeit implementieren.
So konnten wir asynchron arbeiten und uns dann mit Reviews gegenseitig korrigieren,
sodass wir die Grundlagen sicher hatten. 

Jeder hat für seine Funktionen die nötigen Unit-Tests geschrieben und war dafür verantwortlich, dass die Einzelteile schon funktionsfähig waren.

So konnten wir uns dann gemeinsam daran setzen, 
die main zu implementieren, was durch die selbstständige Vorarbeit deutlich vereinfacht wurde. 
Mit der vorerst fertigen main haben wir dann das Programm endlich zusammengesetzt testen können. 
Dabei sind uns dann, wie zu erwarten, noch weitere Fehler aufgefallen, die wir dann zusammen fixen konnten.

### 1.3 Zusammenfassung

Insgesamt haben wir herausgefunden, dass für unser Team vor allem eine klare und strukturierte Arbeitsweise am besten funktioniert hat. Zunächst haben wir die Umsetzung gemeinsam geplant und die Aufgaben sinnvoll aufgeteilt. Anschließend wurden die einzelnen Teilbereiche eigenständig bearbeitet, gegenseitig reviewed und am Ende gemeinsam integriert und getestet.

So in der Form haben wir beide Aufgabenteile gelöst.

## 2.0 Alternative Optionen
>Welche anderen Optionen hatten wir hinsichtlich der Struktur oder Umsetzung?

Andere Optionen waren:
1. Wir haben überlegt, andere Datenstrukturen zu verwenden z.B.:
    - Für das Parkhaus haben wir uns zwischen einem Array und einer Linkedlist für das Array entschieden.
    - Teilweise hatten wir überlegt, kleinere Datentypen zu verwenden um Speicher zu sparen.
    - Wir hatten überlegt die Fahrzeug structs direkt im Array zu speichern
2. Wir haben überlegt die Simloop auszulagern um die main noch kürzer zu halten

## 3.0 Begründung der Entscheidungen
>Warum haben wir uns gegen die anderen Optionen entschieden bzw. für die gewählte Variante gemeinsam entschieden?

1. Warum wir uns für das Array entschieden haben:
    - Unser Parkhaus hat eine festgelegte Größe, die sich im Programmverlauf nicht ändert. Hierfür ist ein Array perfekt geeignet, da es einmal mit dieser Größe initialisiert werden kann.
    Der Vorteil einer Linked List wäre daher nicht relevant. Zusätzlich können wir mit einem Array auf jeden Index in O(1) zugreifen, während der Zugriff bei einer Linked List O(n) dauern würde.
    - Für die Datentypen haben wir so gut es geht versucht die speicherschonendste Option zu wählen. Trotzdem gab es Situationen wo wir lieber auf nochmal sicher gegangen sind und die paar verlorenen Bits in Kauf genommen haben um einen fehlerfreien Code garantieren zu können. Hier war immer eine Risikoabwägung unsererseits nötig. 
    - Wir haben uns recht schnell dafür entschieden das Parkhaus als Array, welches Pointer auf die Fahrzeuge enthält zu erstellen. Dies hat den Vorteil, dass nicht für jede Operation ein ganzes Struct ins Array kopiert und an die Funktionen übergeben werden muss, sondern eben nur Pointer auf diese. Das führt zu einer effizienteren Speichernutzung und schnellere Laufzeit. Um einen leeren Platz darstellen zu können, haben wir NULL Pointer benutzt. In der Praxis hat sich dieser Ansatz als gute Entscheidung herausgestellt.

2. Warum wir uns gegen ein extra file für Simloop entschieden haben:
Wir waren der Meinung, dass die extra Modularisierung keinen wirkliche Mehrwert gebracht hätte, und eher dazu geführt hätte, dass die Struktur komplexer und damit unleserlicher geworden wäre. Da der Simloop auch nicht sehr lange ist, wird die main.c damit auch nicht unnötig lang.


## 4.0 Herausforderungen
>Gab es Schwierigkeiten, Herausforderungen bei der Zusammenarbeit?

- Eine Herausforderung bei der Zusammenarbeit war, die Aufgaben fair und gleichmäßig zu verteilen, 
da wir innerhalb der Gruppe unterschiedlich schnell waren und unterschiedliche Vorkenntnisse mitbrachten.
Durch den Unterschied an Programmierfähigkeiten, hat sich auch das gegenseitige reviewen als kleine Herausforderung dargestellt, weil die meisten Fehler
meistens von der selben Person erkannt und kommentiert wurden. Mit der Zeit hat sich das aber deutlich verbessert, da man gelernt hat, worauf man achten muss und wie man Code am besten lesen kann und da unsere Programmierkentnisse sich ständig verbessert haben.

- Zeitmanagement war für uns auch eine Herausforderung, da wir nebenbei auch viel Zeit in die anderen Fächer investieren mussten. Auch haben wir am Anfang unterschätzt wie lange es dauert, alles richtig zu testen, GitHub zu pflegen und die Dokumentation zu schreiben.

- Auch mussten wir lernen wie man Online Ressourcen und KI, sinnvoll nutzt ohne sich zu sehr darauf zu verlassen oder den Code einfach zu kopieren. Wir haben KI zur Wissensaneignung und Recherche von Funktionen und Algorithmen genutzt, aber immer darauf geachtet, dass wir den Code selbst schreiben und verstehen.



## 5.0 Positive Erfahrungen in der Teamarbeit
>Was ist uns im Team einfach gefallen bzw. sehr gut gelungen?

- Aus dem Grund, dass wir nicht alle gleich gut programmieren können, haben wir noch mehr darauf geachtet, dass jeder trotzdem ähnlich komplexe Aufgaben bekommt und bearbeitet.

- Wenn jemand Fragen hatte oder die Funktionsweise nicht verstand, konnten wir uns alles gegenseitig gut erklären. 

- Auch hatten wir das Gefühl, dass die Arbeitsteilung sehr gut gelaufen ist und niemand über-/unterfordert war. Wir konnten uns gut auf Lösungen einigen und haben die wichtigen Entscheidungen immer zusammen getroffen. Generell war die Zusammenarbeit sehr harmonisch, wir hatten keine großen Meinungsverschiedenheiten und sind immer schnell auf einen Nenner gekommen.

- Wir haben uns oft zusammengesetzt, um an den Aufgaben zu arbeiten. 
Das hat sehr geholfen, dass wir alle am selben Strang ziehen. 
Aus diesem Grund gab es auch mehrere Branches, die in Zusammenarbeit, aber eben von einem Account committet und gemerget wurden. 
Dazu sollten aber Anmerkungen in den Commits stehen, damit klar ist, was wir zusammen gemacht haben. Außerdem haben wir im Kanban Board die Tasks immer korrekt verteilt.

## 6.0 Technische Schwierigkeiten

### 6.1 Git-Branches auf einem case-insensitiven Dateisystem
Wir hatten auch mit Git das ein oder andere Problem. So ist es und z.B. passiert, dass wir zwei Branches hatten, welche sich nur durch Groß- und Kleinschreibung unterschieden. 
Dadurch konnten wir lokal nicht mehr pullen, da das Filesystem auf unseren Rechnern case-insensitive ist und somit zwischen den Branches nicht unterscheiden konnte.
Dies konnten wir lösen, indem wir auf dem Remote den fehlerhaften Branch gelöscht haben und dann mit dem Befehl 
`git fetch --prune`
 die gelöschten Branches des Origins synchronisiert haben.

### 6.2 Iteration über das Parkhaus-Array
Eine andere Schwierigkeit, die wir am Anfang überkommen mussten, war die Frage wie wir durch das Parkhaus Array durchlaufen können. Da die Anzahl der Parkplätze in der main.c gespeichert ist, hätten wir bei jedem Aufruf von Funktionen aus parkhaus.c diesen Wert übergeben müssen. Wir haben uns von Anfang an dagegen entschieden, da dies nur zu einer höheren Komplexität in der Implementierung führt. Wir wollten eine Lösung, die seperat, nur lokal in parkhaus.c funktioniert, aber trotzdem Arrays jeglicher Größe durchlaufen kann.


So kamen wir auf die Idee einen "End_Point" einzubauen. Dieser hat die einzigartige `vehicle_id = -1` und wird beim initialisieren des Arrays im Index[Anzahl_Parkplätze], also im letzten Parkplatz + 1 gespeichert.


So müssen wir zum durchlaufen des Arrays nur schauen, ob der aktuelle Wert die Eigenschaft `vehicle_id != -1` hat. Hier ist es wichtig, dass die leeren Plätze mit NULL belegt sind und eine Abfrage `NULL->vehicle.id` nicht möglich ist. Deshalb wird in der while-Schleife erst geprüft, ob der aktuelle Wert == NULL ist und erst wenn dies nicht der Fall wird er dereferenziert. 
So haben wir eine wie wir finden elegante und vorallem autonome Methode das Array durchzulaufen.