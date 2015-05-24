#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char **argv) {
    int c, fd, flags, length;
    void *ptr;

    flags = O_RDWR | O_CREAT;
    while((c = getopt(argc, argv, "e")) != -1) {
        switch(c) {
            case 'e':
                flags |= O_EXCL;
                break;
            default:
                printf("invalid arg: %c\n", c);
        }
    }

    if(optind != argc - 2) {
        printf("Usage: %s [-e] <filename> <length>\n", argv[0]);
        exit(1);
    }
    length = atoi(argv[argc - 1]);

    fd = shm_open(argv[argc - 2], flags, MODE);
    if(fd < 0) {
        perror("shm_open error");
        exit(1);
    }

    ftruncate(fd, length);
    ptr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    exit(0);
}
