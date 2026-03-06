/*mit diesem File können wir fürs implementieren die einzelnen Funktionen unserer Files einmal testen.
Ruft im richtigen Block einfach die Funktionen auf die ihr testen wollt und lasst euch den return 
ausprinten.*/

#include "../include/queue.h"
#include "../include/vehicle.h"
#include "../include/parkhaus.h"
#include "../include/statistics.h"
#include "../include/sim_parameters.h"
#include <stdio.h>
#include <stdlib.h>

void queue_test(){
    queue *my_queue = init_queue();
    if (my_queue == NULL) {
        printf("Failed to initialize queue.\n");
        return;
    }

    enqueue(my_queue, 1, 60, 0);
    enqueue(my_queue, 2, 120, 5);
    enqueue(my_queue, 3, 30, 10);

    printf("Queue after enqueues:\n");
    print_queue(my_queue);

    vehicle *v = dequeue(my_queue);
    if (v != NULL) {
        printf("Dequeued vehicle ID: %d\n", v->vehicle_id);
        free(v);
    }

    printf("Queue after dequeue:\n");
    print_queue(my_queue);

    free_queue(&my_queue);
    printf("Queue freed.\n");
}

void parkhaus_test(){

}

void statistics_test(){

}

void sim_parameters_test(){

}
int main(){
    queue_test();
    //parkhaus_test();
    //statistics_test();
    //sim_parameters_test();
}