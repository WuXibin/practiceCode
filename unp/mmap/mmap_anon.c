#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

struct shared {
    sem_t sem;
    int count;
} shared;

int main(int argc, char **argv) {
    int loopcount;
    struct shared *addr;
    pid_t pid;

    if(argc != 2) {
        printf("Usage: %s <loopcount>\n", argv[0]);
        exit(1);
    }

    loopcount = atoi(argv[1]);

    addr = (struct shared*)mmap(NULL, sizeof(shared), 
            PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(addr == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    setbuf(stdout, NULL);

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
