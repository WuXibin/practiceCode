#include "allocator.h"

int main() {
    int *vec = (int *)csapp_malloc(10 * sizeof(int));
    char *vec2 = (char *)csapp_malloc(13);
    csapp_free(vec);
    char *buf = (char *)csapp_malloc(40);
    csapp_free(vec2);
    csapp_free(buf);
    return 0;
}
