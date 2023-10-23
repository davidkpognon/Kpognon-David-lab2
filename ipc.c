// TODO: add the appropriate header files here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define SHARED_MEM_NAME "/lab2"

/**************************************************************
 *  ipc_create - creates a shared memory object called lab2 and
 *               returns a char pointer to the memory shared
 *               memory object.
 * 
 *  size - is the size of the memory object to create.
 *   
 ***************************************************************/
char* ipc_create(int size){
    /* shared memory file descriptor */
    int fd;
    /* pointer to shared memory obect */
    char* ptr;
    //int sizee = size;

    // TODO: create the shared memory object called lab2
    fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd==-1) {
        perror("shm_open");
        exit(1);
    }


    // TODO: configure the size of the shared memory object 
    if (ftruncate(fd, size) == -1) {
        perror("ftruncate");
        exit(1);
    }


    // TODO: memory map the shared memory object */
    ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    close(fd); // Close the file descriptor

    return ptr;
}

double ipc_read(void* shared_memory) {
    return *((double*)shared_memory);
}



/**************************************************************
 * ipc_close - closes the ipc communication channel that was
 *             created with ipc_create.
 * 
 **************************************************************/
void ipc_close(){
    //munmap(fd, sizee);
    shm_unlink("lab2");
}