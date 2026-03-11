# Begründungen und Erklärungen für unser Projekt

## 1. Wie haben Sie die Aufgabenstellung gelöst?

Bevor wir beginnen konnten, wirklich autonom zu arbeiten, haben wir Folgendes noch in Zusammenarbeit erledigt:
    - am Anfang haben wir uns zusammengesetzt und gemeinsam einen Plan erstellt
    - wir haben alle Issues im GitHub repo gesammelt um einen Überblick zu bekommen 
    - ein grundlegendes Flowchart für main erstellt, das alle Funktionen und Logiken des Programms beinhaltet
    - fesgelegt, dass die Haupt Header-Files sind Parkhaus, Queue und statistics 
    - dann haben wir aufgeteilt, dass Nikolai die Queue, Julius das Parkhaus und Esther die Statistiken macht
dann konnte jeder von uns an dem Pseudocode seiner Header Datei arbeiten.

Für die schnelle Kommunikation haben wir auch eine WhatsApp Gruppe erstellt und uns ggf darüber informiert und Fragen gestellt.
Wir haben darauf geachtet, dass jeder Merge request von mindestens einer anderen Person (bei wichtigen Merges beide anderen) reviewed und erst dann gemerged wird.
Wenn wir zusammen an Funktionen und Issues gearbeitet haben, haben wir das größtenteils in den commit messages dazu geschreiben.

Während der Arbeit an unseren Header-Dateien fiel uns auf, dass uns einiges strukturell noch fehlt, wie z.B:
    - sim_parameters.h und sim_parameters.c : um die eingegebenen Simulationsparameter mehrmals zu nutzen, 
    haben wir das Lesen und speichern dieser Parameter in einer eigenen Datei ausgelagert
    - vehicle.h : da wir die Informationen von den Fahrzeugen in mehreren Funktionen und Header-Dateien nutzen,
    haben wir diesen struct auch ausgelagert

Unsere Arbeitsweise im zweiten Teil der Aufgabe lief deutlich einfacher, da wir schon Plan und Pseudocode hatten.
Da wir die verschiedenen Teile des Programms gut aufgeteilt hatten, konnten wir queue.c, parkhaus.c, sim_parameters.c und
statistics.c gut in Einzelarbeit implementieren.
So konnten wir asynchron arbeiten und uns dann mit Reviews gegenseitig korrigieren,
sodass wir die Grundlagen sicher hatten. 

Jeder hat für seine Funktionen die nötigen Unit-Tests geschrieben und war dafür verantwortlich, dass die Einzelteile schon funktionsfähig waren.

So konnten wir uns dann gemeinsam daran setzen, 
die main zu implementieren, was durch die selbstständige Vorarbeit deutlich vereinfacht wurde. 
Mit der vorerst fertigen main haben wir dann das Programm endlich zusammengesetzt testen können. 
Dabei sind uns dann, wie zu erwarten, noch weitere Fehler aufgefallen, die wir dann zusammen fixen konnten.

## 2. Welche anderen Optionen hatten Sie im Team hinsichtlich der Struktur oder Umsetzung gehabt?

Andere Optionen waren:
1. Wir haben überlegt, andere Datenstrukturen zu verwenden z.B.:
    - Für das Parkhaus haben wir uns zwischen einem Array und eine Linkedlist für ein Array entscheide.
    - Teilweise hatten wir überlegt, kleinere Datentypen zu verwenden um Speicher zu sparen.
2. Wir haben überlegt die Simloop auszulagern um die main noch kürzer zu halten

## 3. Warum haben Sie sich gegen die anderen Optionen entschieden bzw. für die gewählte Variante gemeinsam entschieden?

1. Warum wir uns für das Array entschieden haben:
    - Unser Parkhaus hat eine feste Größe, daher passt ein Array perfekt, da es ebenfalls eine feste Größe hat.
    Der Vorteil einer Linked List wäre daher nicht relevant. Zusätzlich können wir mit einem Array auf jeden Index in O(1) zugreifen,
    während der Zugriff bei einer Linked List O(n) dauern würde.
    - Die Verwendung von kleineren Datentypen hätte zu viel Komplexität und potenzielle Fehlerquellen hinzugefügt, was unserer Meinung nach nicht der geringfügigen Menge an gespartem Speicher entspricht.

2. Warum wir uns gegen ein extra file für Simloop entschieden haben:
Wir waren der meinung, dass die extra modularisierung keinen wirkliche mehrwert gebrcaht hätte, und ehr dazu geführt hätte, dass die strukut komplexer und damit 


## 4. Gab es Schwierigkeiten, Herausforderungen bei der Zusammenarbeit?

Eine Herausforderung bei der Zusammenarbeit war, die Aufgaben fair und gleichmäßig zu verteilen, 
da wir innerhalb der Gruppe unterschiedlich schnell waren und unterschiedliche Vorkenntnisse mitbrachten.
Durch den Unterschied an Programmierfähigkeiten, hat sich auch das gegenseitige reviewen als kleine Herausforderung dargestellt, weil die meisten Fehler
meistens von der selben Person erkannt und kommentiert wurden.


## 5. Was ist Ihnen im Team einfach gefallen bzw. sehr gut gelungen?

Aus dem Grund, dass wir nicht alle gleich gut programmieren können, haben wir noch mehr darauf geachtet, 
dass jeder trotzdem ähnlich komplexe Aufgaben bekommt und bearbeitet.

Wenn jemand Fragen hatte oder die Funktionsweise nicht verstand, konnten wir uns alles gegenseitig gut erklären. 

Auch hatten wir das Gefühl, dass die Arbeitsteilung sehr gut gelaufen ist und niemand über-/unterfordert war.
Wir konnten uns gut auf Lösungen einigen und haben die wichtigen Entscheidungen immer zusammen getroffen. Generell war die Zusammenarbeit sehr harmonisch, wir hatten keine großen Meinungsverschiedenheiten und sind immer schnell auf einen Nenner gekommen.

Wir haben uns oft zusammengesetzt, um an den Aufgaben zu arbeiten. 
Das hat sehr geholfen, dass wir alle am selben Strang ziehen. 
Aus diesem Grund gab es auch mehrere Branches, die in Zusammenarbeit, aber eben von einem Account committet und gemerget wurden. 
Dazu sollten aber Anmerkungen in den Commits stehen, damit klar ist, was wir zusammen gemacht haben.

## 6. Technische Schwierigkeiten

Wir hatten auch mit Git das ein oder andere Problem. Z. B. ist es uns passiert, dass wir zwei Branches hatten, welche sich nur durch Groß- und Kleinschreibung unterschieden. 
Dadurch konnten wir lokal nicht mehr pullen, da das Filesystem auf unseren Rechnern case-insensitive ist und somit zwischen den Branches nicht unterscheiden konnte.
Dies konnten wir lösen, indem wir auf dem Remote den fehlerhaften Branch gelöscht haben und dann mit dem Befehl "git fetch --prune" die gelöschten Branches des Origins synchronisiert haben.

//@Julius explain solution for end element in Array
