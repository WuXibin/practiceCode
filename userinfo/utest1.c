#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    int n1, n2, n3;

    printf("~~~start test1\n");
    char *str1 = "17511:1.27";
    sscanf(str1, "%d:%d.%d", &n1, &n2, &n3); 
    printf("%d %d %d\n", n1, n2, n3);
    assert(n1 == 17511);
    assert(n2 == 1);
    assert(n3 == 27);
    printf("~~~test1 success\n");

    printf("~~~start test2\n");
    char *str2 = "20287:0.97";
    sscanf(str2, "%d:%d.%d", &n1, &n2, &n3); 
    printf("%d %d %d\n", n1, n2, n3);
    assert(n1 == 20287);
    assert(n2 == 0);
    assert(n3 == 97);
    printf("~~~test2 success\n");

    printf("~~~start test3\n");
    char *str3 = "7:4.08";
    sscanf(str3, "%d:%d.%d", &n1, &n2, &n3); 
    printf("%d %d %d\n", n1, n2, n3);
    assert(n1 == 7);
    assert(n2 == 4);
    assert(n3 == 8);
    printf("~~~test3 success\n");

    printf("~~~start test4\n");
    char *str4 = "0";
    int n = sscanf(str4, "%d:%d.%d", &n1, &n2, &n3); 
    printf("%d %d %d\n", n1, n2, n3);
    assert(n == 1);
    assert(n1 == 0);
    assert(n2 == 0);
    assert(n3 == 0);
    printf("~~~test4 success\n");

    return 0;
}
