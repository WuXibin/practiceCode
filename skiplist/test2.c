#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MaxLevel    16
#define Fraction    25          /* percentage */

static int skp_random_level(int max_level, int fraction) {
    int level = 1;

    while(1) {
        int r = rand() % 100; 
        if(r >= fraction) break;

        if(++level == max_level) break;
    }

    return level;
}

int main() {
    int count[MaxLevel];
    memset(count, 0, MaxLevel * sizeof(int));

    srand(time(NULL));

    for(int i = 0; i < 65536; i++) {
        ++count[skp_random_level(MaxLevel, Fraction) - 1];
    }

    for(int i = 0; i < MaxLevel; i++) {
        printf("Level=%d, count=%d\n", i+1, count[i]);
    }

    return 0;
}
