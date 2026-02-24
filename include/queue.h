/* queue.h

struct queue:
* firstCar: (*vehicle) pointer to the first car in the queue
* lastCar: (*vehicle) additional pointer to the last car in the queue to make adding cars more efficient {O(1) instead of O(n)}
* size: (int) store the number of cars in the queue because this information is accessed often

struct vehicle:
* vehicle_id (int) unique identifier for the vehicle
* remaining_parktime (int) this is specified by the instructions but actually it's redundant information because we can calculate this from
* time_of_entry (int) Zeitpunkt, zu dem das Fahrzeug in das Parkhaus einfährt
* time_of_arrival (int) (Wird gebraucht, um die Wartezeit zu berechnen)
* random_park_duration (int) (beachte max. Parkdauer)

queue init() returns an empty queue

int enqueue(*queue queue, int id, int parking_time, int current_time) adds a vehicle(with the specified parameters) 
to the end of the specified queue and returns 1 if successful, 0 if failed
This function doesn't accept a vehicle struct directly, to have more control over memory management and to avoid potential issues with incorrectly (not stored in the Heap) initialized vehicle structs being passed to the function.
Instead, it creates a new vehicle struct internally and adds it to the queue.

int dequeue(*queue) removes the first vehicle, returns 1 if a car was removed and 0 if the specified queue was empty

int print_queue(*queue) prints the queue for debugging purposes; returns 1 if successful, 0 if empty

(getLength wird nicht benötigt, da die Länge der Queue in der Queue-Struktur gespeichert wird; somit ist die Laufzeit O(1) anstatt O(n) wie bei einer Implementierung ohne size-Variable)
*/