#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_SIZE 1024
#define SERV_PORT 8080
#define BACK_LOG 10

#define MAX_EVENTS 100

static int echo(int fd);

int main(int argc, char **argv) {
    int servfd;
    struct sockaddr_in servaddr;

    servfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(servfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(servfd, BACK_LOG);

    int epollfd, nfds;
    struct epoll_event ev, events[MAX_EVENTS];
    epollfd = epoll_create(10);
    ev.events = EPOLLIN;
    ev.data.fd = servfd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, servfd, &ev);
    
    int i, clifd;
    while(1) {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1); 
        for(i = 0; i < nfds; i++) {
            if(events[i].data.fd == servfd) {
                clifd = accept(servfd, NULL, NULL);
                printf("new connection\n");
                fcntl(clifd, F_SETFL, O_NONBLOCK);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = clifd;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, clifd, &ev);
            } else {
                if(echo(events[i].data.fd) < 0)
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
            }
        }
    }
}

static int echo(int fd) {
    int n;
    char buf[MAX_SIZE];
    while(1) {
        n = read(fd, buf, MAX_SIZE);
        if(n < 0) {                          
            if(errno == EAGAIN || errno == EWOULDBLOCK) {       //No More Data
                printf("No more data\n");
                return 0;
            } else {                                            //ERROR 
                printf("Error occur!\n");
                return -1;
            }
        }
        if(n == 0) {     
            printf("client close connection\n");                //EOF
            return -1;
        }
        write(fd, buf, n);
    }
}
