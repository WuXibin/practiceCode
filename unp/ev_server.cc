#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <event2/event.h>

#define MAX_BUFSIZE 1024

typedef struct {
    struct event *ev;
} event_ctx;

void ev_callback(int fd, short what, void *arg) {
    printf("ev_callback\n");
    char buf[MAX_BUFSIZE];
    if(what & EV_READ) {
        int n;
        while(1) {
            n = read(fd, buf, MAX_BUFSIZE);
            if(n <= 0) break;
            buf[n] = 0;
            printf("receive: %s\n", buf);
            sleep(1);
            write(fd, buf, n);  //echo
        }
        if(n < 0 && errno == EAGAIN) {
            printf("EAGAIN\n");
            return;
        }
        printf("Client [%d] disconnect, free event\n", fd);
        event_ctx *ctx = (event_ctx *)arg;
        ::event_del(ctx->ev);
    }
}

void do_accept(int fd, short what, void *arg) {
    printf("do_accept\n");
    struct event_base *base = (struct event_base *)arg;
    while(1) {
        int clifd = accept(fd, NULL, NULL);
        if(clifd < 0) return;
        ::evutil_make_socket_nonblocking(clifd);
        printf("Client [%d] connect.\n", clifd);

        struct event *ev;
        event_ctx *ctx = (event_ctx *) malloc(sizeof(event_ctx));
        ev = ::event_new(base, clifd, EV_READ | EV_PERSIST, ev_callback, ctx);
        ctx->ev = ev;
        ::event_add(ev, NULL);
    }
}

int main(){
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(5555);
    sin.sin_addr.s_addr = 0;

    int servfd = socket(AF_INET, SOCK_STREAM, 0);
    ::evutil_make_socket_nonblocking(servfd);
    bind(servfd, (struct sockaddr *)&sin, sizeof(sin));
    listen(servfd, 10);

    struct event_base *base;
    base = ::event_base_new();
    
    struct event *ev;
    ev = ::event_new(base, servfd, EV_READ | EV_PERSIST, do_accept, base);
    ::event_add(ev, NULL);
    ::event_base_dispatch(base);
    return 0;
}
