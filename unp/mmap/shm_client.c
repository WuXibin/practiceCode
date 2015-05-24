#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

int main(int argc, char **argv) {
    int fd, nloops;
    sem_t *sem;
    int *ptr;

    if(argc != 4) {
        printf("Usage: %s <semname> <shmname> <#nloops>\n", argv[0]);
        exit(1);
    }
    nloops = atoi(argv[3]);

    /* create semaphore */
    sem = sem_open(argv[1], O_RDWR);
    if(sem == SEM_FAILED) {
        perror("sem_open error");
        exit(1);
    }

    /* create shared memory object */
    fd = shm_open(argv[2], O_RDWR, 0);
    if(fd < 0) {
        perror("shm_open error");
        exit(1);
    }

    ptr = (int *)mmap(NULL, sizeof(int), 
            PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
    if(ptr == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    close(fd);

    for(int i = 0; i < nloops; ++i) {
        sem_wait(sem);
        printf("pid=%ld, value=%d\n", (long)getpid(), (*ptr)++);
        sem_post(sem);
    } 

    exit(0);
}
