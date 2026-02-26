#ifndef VEHICLE_H
#define VEHICLE_H


struct vehicle
{
    int vehicle_id; //unique identifier for the vehicle
    int remaining_parktime; //this is specified by the instructions but actually it's redundant information because we can calculate this from
    int time_of_entry; //time of entry into the parking lot is used to calculate the remaining parking time
    int time_of_arrival; // Us used to calculate the waiting time in the queue
    int random_park_duration; // between 1 and max_parking_time
};

#endif