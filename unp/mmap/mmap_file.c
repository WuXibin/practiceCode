#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define MMAP_SEM "/mmap_sem"

struct shared {
    sem_t sem;
    int count;
} shared;

int main(int argc, char **argv) {
    int fd, loopcount;
    struct shared *addr;
    pid_t pid;

    if(argc != 3) {
        printf("Usage: %s <filename> <loopcount>\n", argv[0]);
        exit(1);
    }

    loopcount = atoi(argv[2]);

    fd = open(argv[1], O_RDWR | O_CREAT, MODE);
    if(fd < 0) {
        perror("open error");
        exit(1);
    }
    write(fd, &shared, sizeof(shared));

    addr = (struct shared*)mmap(NULL, sizeof(shared), 
            PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    setbuf(stdout, NULL);

    /*
    sem = sem_open(MMAP_SEM, O_CREAT | O_EXCL, MODE, 1);
    if(sem == SEM_FAILED) {
        perror("sem_open error");
        exit(1);
    }
    sem_unlink(MMAP_SEM);
    */
    sem_init(&addr->sem, 1, 1);

    if((pid = fork()) == 0) {   /* child */
        for(int i = 0; i < loopcount; ++i) {
            sem_wait(&addr->sem); 
            printf("child: %d\n", addr->count++);
            sem_post(&addr->sem);
        }

        exit(0);
    }

    for(int i = 0; i < loopcount; ++i) {
        sem_wait(&addr->sem); 
        printf("parent: %d\n", addr->count++);
        sem_post(&addr->sem);
    }

    exit(0);
}
