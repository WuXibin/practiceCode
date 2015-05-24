#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int fd;
    int *ptr;
    struct stat st;

    if(argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1); 
    }

    fd = shm_open(argv[1], O_RDWR, 0);
    if(fd < 0) {
        perror("shm_open error");
        exit(1);
    }
    fstat(fd, &st);
    ptr = (int *)mmap(NULL, st.st_size, 
            PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    for(int i = 0; i < st.st_size; ++i) {
        *ptr++ = i % 256;
    }

    exit(0);
}
