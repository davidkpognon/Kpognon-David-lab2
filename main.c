// TODO: add the appropriate head files here
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "lab2.h"

#define SHARED_MEM_NAME "/lab2"
/************************************************************\
 * get_arguments - returns the command line arguments not
 *                 including this file in an array with the
 *                 last element as null.  This is the format
 *                 that the execvp() function requires.
 * 
 * For example:  ./time ls -l
 * will return an array consisting of {"ls","-l", NULL}
 ************************************************************/
char** get_arguments(int argc, char** argv){
    int arg_length = argc;
    char**  cmd_args = NULL;

    if (arg_length > 0){
        cmd_args = (char**)malloc(sizeof(char*)*arg_length);
    }
    for(int i = 0; i < arg_length-1; i++){
        cmd_args[i] = argv[i+1];
    }
    cmd_args[arg_length-1] = NULL;
    return cmd_args;
}


int main(int argc, char** argv)
{
    pid_t pid;
    int status;
    char* command = NULL;
    char** command_args = NULL;
    char* ipc_ptr = NULL; // pointer to shared memory
    struct timeval start_time;
    struct timeval current_time;

    if (argc < 2){
        fprintf(stderr,"SYNOPSIS: %s <cmd> <cmd arguments>\n",argv[0]);
        return 1;
    }
    
    // size_t shared_mem_size = sizeof(double);
    // void* shared_memory = mmap(NULL, shared_mem_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    // if (shared_memory == MAP_FAILED) {
    //     perror("mmap");
    //     exit(1);
    // }
    // TODO: call ipc_create to create shared memory region to which parent
    //       child have access.
    ipc_create(4096);
    

    /* fork a child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork failed!");
        return 2;
    }
    else if (pid == 0) { /*child process */
        // TODO: use gettimeofday to log the start time
        gettimeofday(&start_time, NULL);
        time_t start_time_seconds = start_time.tv_sec;


        // TODO: write the time to the IPC
        
        // TODO: get the list of arguments to be used in execvp() and 
        // execute execvp()
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(1);

    }
    else { /* parent process */
        // TODO: have parent wait and get status of child.
        //       Use the variable status to store status of child. 
        wait(NULL);
        
        // TODO: get the current time using gettimeofday
        gettimeofday(&current_time, NULL);
        time_t current_time_seconds = current_time.tv_sec;
        // TODO: read the start time from IPC
       // ipc_read(lab2);
        // TODO: close IPC
        ipc_close();
        shm_unlink(SHARED_MEM_NAME);
        // NOTE: DO NOT ALTER THE LINE BELOW.
        printf("Elapsed time %.5f\n",elapsed_time(&current_time, &start_time));
    }
    
    return status;
}