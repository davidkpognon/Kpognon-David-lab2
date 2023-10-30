#include <sys/time.h>

double elapsed_time(struct timeval* start_time, struct timeval* end_time){
    //TODO: return the difference between end_time and start_time.
    // double elapsed_time;
    // elapsed_time = difftime(end_time, start_time); 
    double sec = (double)(end_time->tv_sec - start_time->tv_sec);
    double sec2 = (double)(end_time->tv_usec - start_time->tv_usec) / 1e6;
    return sec+sec2;
    // return difftime(end_time, start_time);
}