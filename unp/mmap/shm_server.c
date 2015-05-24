#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char **argv) {
    int fd;
    sem_t *sem;
    void *ptr;

    if(argc != 3) {
        printf("Usage: %s <semname> <shmname>\n", argv[0]);
        exit(1);
    }

    /* create semaphore */
    sem_unlink(argv[1]);
    sem = sem_open(argv[1], O_RDWR | O_CREAT, MODE, 1);
    if(sem == SEM_FAILED) {
        perror("sem_open error");
        exit(1);
    }
    sem_close(sem);

    /* create shared memory object */
    shm_unlink(argv[2]);
    fd = shm_open(argv[2], O_RDWR | O_CREAT, MODE);
    if(fd < 0) {
        perror("shm_open error");
        exit(1);
    }

    ftruncate(fd, sizeof(int));

    ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
    if(ptr == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    close(fd);

    exit(0);
}
