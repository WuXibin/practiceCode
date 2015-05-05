#include <stdlib.h>
#include <stdio.h>
#include "skiplist.h"

static int key_comp(void *, void *);
static void key_desc(void *);
static void val_desc(void *);

int main() {
    skiptype type;
    type.key_comp = key_comp;
    type.key_desc = key_desc;
    type.val_desc = val_desc;

    skiplist *skp = skp_create(type);

    for(int i = 0; i < 65536; ++i) {
        int *key = (int *)malloc(sizeof(int));
        *key = i;

        char *val = (char *)malloc(100);
        snprintf(val, 100, "key is %d", i);

        skp_insert(skp, key, val);
    }    

    printf("cur_level=%d, cur_nodes=%d\n", skp->cur_level, skp->cur_nodes);

    for(int i = 0; i < 100; ++i) {
        int key = rand() % 65536;
        printf("search key=%d\n", key);
        if(skp_search(skp, &key) != NULL) {
            printf("~~~found!\n");
        }
    }

    skp_destroy(skp);

    return 0;
}


static int key_comp(void *k1, void *k2) {
    int key1 = *((int *)k1), key2 = *((int *)k2);

    if(key1 < key2) {
        return -1;
    } else if(key1 > key2) {
        return 1;
    } else {
        return 0;
    }
}


static void key_desc(void *k) {
    int *key = (int *)k;
    
    free(key); 
}


static void val_desc(void *v) {
    char *val = (char *)v;
    
    free(val);
}
