#include <stdlib.h>
#include <string.h>
#include "skiplist.h"

static int skp_random_level(int max_level, int fraction) {
    int level = 1;

    while(1) {
        int r = rand() % 100; 
        if(r >= fraction) break;

        if(++level == max_level) break;
    }

    return level;
}


skiplist* skp_create(skiptype type) {
    skiplist* skp = (skiplist *)malloc(sizeof(skiplist));
    memset(skp, 0, sizeof(skiplist));
    skp->type = type;

    return skp;
}


listnode* skp_search(skiplist *skp, void *key) {
    int level = skp->cur_level - 1;
    if(level < 0) {
        return NULL;
    }

    listnode *p = skp->forward[level];
    for(int i = level; i >= 0; --i) {
        while(p && skp->type.key_comp(p->key, key) < 0) {
            p = p->forward[i];
        }
    }
    p = p->forward[0];
    if(p && skp->type.key_comp(p->key, key) == 0) {
        return p;
    }

    return p;
}

void skp_insert(skiplist *skp, void *key, void *data) {
     
}
