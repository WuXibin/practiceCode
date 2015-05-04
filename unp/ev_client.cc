#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <event2/event.h>

void ev_callback(int fd, short what, void *arg) {
    struct event **evp = (struct event **)arg;
    if(what & EV_READ) {
        while(1) {
            char buf[1024];
            int n = read(fd, buf, sizeof(buf));
            if(n > 0) {
                buf[n] = 0;
                printf(">>%s\n", buf);
            } else if(n < 0 && errno == EAGAIN) {
                printf("EAGAIN\n");
                return;
            } else {
                printf("Error: %s\n", strerror(errno));
                ::event_free(*evp);
                return;
            }
        }
    }
    if(what & EV_TIMEOUT) {
        struct timeval tv;
        char buf[128];
        gettimeofday(&tv, NULL);
        struct tm *tmp = localtime(&tv.tv_sec);
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tmp);
        printf("event timeout: %s %ld\n", buf, tv.tv_usec);
        char msg[] = "Hello World";
        ::event_del(*evp);
        write(fd, msg, strlen(msg));
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        ::event_add(*evp, &tv);
    }
}

int ConnectServer(const char *ip, unsigned port) {
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    inet_pton(AF_INET, ip, (struct sockaddr *)&sin.sin_addr);
    
    int servfd = socket(AF_INET, SOCK_STREAM, 0);
    //::evutil_make_socket_nonblocking(servfd);
    if(connect(servfd, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
        perror("connect error");
        return -1;
    }

    return servfd;
}

int main(int argc, char **argv) {
    if(argc != 3) {
        printf("Usage: %s host_ip host_port\n", argv[0]);
        return -1;
    }

    int servfd = ConnectServer(argv[1], atoi(argv[1])); 
    char msg[] = "Nice to meet you";
    write(servfd, msg, sizeof(msg));
    
    struct event_base *base;
    base = ::event_base_new();
    struct event *ev;
    ev = ::event_new(base, servfd, EV_READ | EV_PERSIST, ev_callback, &ev);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    char buf[128];
    struct tm *tmp = localtime(&tv.tv_sec);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tmp);
    printf("event begin: %s %ld\n", buf, tv.tv_usec);

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    //::event_add(ev, &tv);
    ::event_base_dispatch(base);
    return 0;
}
