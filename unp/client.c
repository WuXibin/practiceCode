#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAX_SIZE 1024

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr); 

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect error");
        return -1;
    }

    int n;
    char buf[MAX_SIZE];
    while(1) {
        n = read(0, buf, MAX_SIZE); 
        if(n == 0) {
            close(sockfd);
            return 0;
        }
        if(write(sockfd, buf, n) < 0) {
            close(sockfd);
            return 0;
        }
        n = read(sockfd, buf, MAX_SIZE);
        if(n <= 0) {
            close(sockfd);
            return 0;
        }
        buf[n] = 0;
        printf("receive: %s\n", buf);
    }
}
