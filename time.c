#include <sys/time.h>

double elapsed_time(struct timeval* start_time, struct timeval* end_time){
    //TODO: return the difference between end_time and start_time.
    double elapsed_time;
    elapsed_time = difftime(end_time, start_time); 
    return elapsed_time;
}