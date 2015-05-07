#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "skiplist.h"

static listnode* skp_search_debug(skiplist *skp, void *key);

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
    listnode *p = skp->forward[0];
    for(int i = 0; i < 50; ++i) {
        printf("key=%d\n", *((int *)p->key)); 
        p = p->forward[0];
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    for(int i = 0; i < 100; ++i) {
        int key = rand() % 65536;
        printf("search key=%d\n", key);
        if(skp_search(skp, &key) != NULL) {
            printf("~~~found!\n");
        } else {
            printf("~~~oops, not found!\n");
        }
    }

    int search_key = 0;
    while(scanf("%d", &search_key)) {
        skp_search_debug(skp, &search_key); 
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

static listnode* skp_search_debug(skiplist *skp, void *key) {
    int level = skp->cur_level - 1;
    if(level < 0) { 
        return NULL;
    }

    int cnt = 0;
    listnode *p = skp->forward[level];
    printf("~~~~~~~~~~key=%d~~~~~~~~~~\n", *((int *)key));
    printf("cnt=%d, head\n", cnt);
    for(int i = level; i >= 0; --i) {
        assert(p);
        ++cnt;
        while(p->forward[i] 
                && skp->type.key_comp(p->forward[i]->key, key) < 0) {
            p = p->forward[i];
            printf("---level=%d, cnt=%d, key=%d\n", i, cnt, *((int *)p->key));
        }
        if(p->forward[i]) {
            printf("-+-level=%d, cnt=%d, key=%d too large\n", i, cnt, *((int *)p->forward[i]->key));
        } else {
            printf("-+-level=%d, cnt=%d, key=nil\n", i, cnt);
        }
    }

    printf("---------------\n");

    ++cnt;
    p = p->forward[0];
    if(p && skp->type.key_comp(p->key, key) == 0) {
        printf("+++cnt=%d, key=%d\n", cnt, *((int *)p->key));
        return p;
    } else {
        if(p) {
            printf("cnt=%d, key=%d end\n", cnt, *((int *)p->key));
        } else {
            printf("cnt=%d, key=nil end\n", cnt);
        }
    }

    return NULL;
}
