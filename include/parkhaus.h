/*
FUNCTION init(Anzahl_Parkplätze) //Parkaus mit der größe der Parkhauses initialisieren
            returns Parkhaus (Array)
            
FUNCTION is_Full(Parkhaus(array)) //Überprüft ob das gegebene Parkhaus noch freie Plätze hat
            return true or false
            
FUNCTION remove_finished_Cars(Parkhaus(array)) //entfernt alle Autos, welche ihre max. Parkdauer überschritten haben
            returns number of removed cars
    
FUNCTION park_Car(Parkhaus(array), Car(struct Vehicle)) //fügt ein gegebenes Auto in den ersten freien Platz der Parkhaus ein
            return wait time of parked car, or Error msg. if full.

FUNCTION get_Used_Spots(Parkhaus(array)) //zählt alle belegten Plätze in einem gegebenen Parkhaus
            returns used_spaces
*/