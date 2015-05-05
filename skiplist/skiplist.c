#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "skiplist.h"

static int skp_random_level(int max_level, int fraction);

skiplist* skp_create(skiptype type) {
    skiplist* skp = (skiplist *)malloc(sizeof(skiplist));
    memset(skp, 0, sizeof(skiplist));
    skp->type = type;

    srand(time(NULL));

    return skp;
}


listnode* skp_search(skiplist *skp, void *key) {
    int level = skp->cur_level - 1;
    if(level < 0) { 
        printf("cur_level[%d] < 0\n", skp->cur_level);
        return NULL;
    }

    int cnt = 0;
    listnode *p = skp->forward[level];
    for(int i = level; i >= 0; --i) {
        assert(p);
        while(p->forward[i] 
                && skp->type.key_comp(p->forward[i]->key, key) < 0) {
            p = p->forward[i];
            ++cnt;
        }
    }

    ++cnt;
    p = p->forward[0];
    if(p && skp->type.key_comp(p->key, key) == 0) {
        printf("cnt=%d\n", cnt);
        return p;
    }

    printf("cnt=%d\n", cnt);

    return NULL;
}

void skp_insert(skiplist *skp, void *key, void *val) {
    listnode *update[MaxLevel];      
    int level = skp->cur_level - 1;

    if(level >= 0) {
        listnode *p = skp->forward[level];
        for(int i = level; i >= 0; --i) {
            assert(p);
            while(p->forward[i] && 
                    skp->type.key_comp(p->forward[i]->key, key) < 0) {
                p = p->forward[i];
            }
            update[i] = p;
        }

        p = p->forward[0];
        if(p && skp->type.key_comp(p->key, key) == 0) {
            p->val = val;
            return;
        }
    }

    listnode *node = (listnode *)malloc(sizeof(listnode));
    node->key = key;
    node->val = val;

    int lv = skp_random_level(MaxLevel, Fraction);
    if(lv <= skp->cur_level) {
        for(int i = 0; i < lv; ++i) {
            node->forward[i] = update[i]->forward[i]; 
            update[i]->forward[i] = node;
        }
    }

    for(int i = skp->cur_level; i < lv; i++) {
        node->forward[i] = skp->forward[i];
        skp->forward[i] = node;
    }
    
    if(lv > skp->cur_level) {
        skp->cur_level = lv;
    }    
    ++skp->cur_nodes;
}

void skp_delete(skiplist *skp, void *key) {
    listnode *update[MaxLevel];
    int level = skp->cur_level - 1;

    if(level < 0) 
        return;

    listnode *p = skp->forward[level];
    for(int i = level; i >= 0; --i) {
        while(p->forward[i] && 
                skp->type.key_comp(p->forward[i]->key, key) < 0) {
            p = p->forward[i]; 
        }
        update[i] = p;
    }

    p = p->forward[0];
    if(p == NULL || skp->type.key_comp(p->key, key) != 0)
        return; 

    for(int i = 0; i < level; ++i) {
        if(update[i]->forward[i] != p) 
            break;

        update[i]->forward[i] = p->forward[i];
    }

    skp->type.key_desc(p->key);
    skp->type.val_desc(p->val);
    free(p);

    while(skp->cur_level > 0 && skp->forward[skp->cur_level - 1] == NULL) {
        --skp->cur_level;
    }
    --skp->cur_nodes;
} 

void skp_destroy(skiplist *skp) {
    while(skp->forward[0]) {
         listnode *p = skp->forward[0];
         skp->forward[0] = p->forward[0];

         skp->type.key_desc(p->key);
         skp->type.val_desc(p->val);
         free(p);
    }

    free(skp);
}

static int skp_random_level(int max_level, int fraction) {
    int level = 1;

    while(1) {
        int r = rand() % 100; 
        if(r >= fraction) break;

        if(++level == max_level) break;
    }

    return level;
}


