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
    int cnt = 0;

    listnode *p = &skp->head;
    for(int i = skp->cur_level - 1; i >= 0; --i) {
        ++cnt;
        while(p->forward[i] && skp->type.key_comp(p->forward[i]->key, key) < 0) {
            p = p->forward[i];
            ++cnt;
        }
    }

    ++cnt;
    p = p->forward[0];
    if(p && skp->type.key_comp(p->key, key) == 0) {
        printf("cnt=%d found!\n", cnt);
        return p;
    }

    printf("cnt=%d not found\n", cnt);

    return NULL;
}

void skp_insert(skiplist *skp, void *key, void *val) {
    listnode *update[MaxLevel];      
    listnode *p = &skp->head;

    for(int i = skp->cur_level - 1; i >= 0; --i) {
        while(p->forward[i] && skp->type.key_comp(p->forward[i]->key, key) < 0) {
            p = p->forward[i];
        }
        update[i] = p;
    }

    p = p->forward[0];
    if(p && skp->type.key_comp(p->key, key) == 0) {
        p->val = val;
        return;
    }

    listnode *node = (listnode *)malloc(sizeof(listnode));
    memset(node, 0, sizeof(listnode));
    node->key = key;
    node->val = val;

    int rand_level = skp_random_level(MaxLevel, Fraction);
    int min_level = (rand_level <= skp->cur_level) ? rand_level : skp->cur_level;
    for(int i = 0; i < min_level; ++i) {
        node->forward[i] = update[i]->forward[i]; 
        update[i]->forward[i] = node;
    }

    if(rand_level > skp->cur_level) {
        for(int i = skp->cur_level; i < rand_level; ++i) {
            node->forward[i] = skp->head.forward[i];
            skp->head.forward[i] = node;
        }
        skp->cur_level = rand_level;
    }
    
    ++skp->cur_nodes;
}

void skp_delete(skiplist *skp, void *key) {
    listnode *update[MaxLevel];
    listnode *p = &skp->head;

    for(int i = skp->cur_level - 1; i >= 0; --i) {
        while(p->forward[i] && skp->type.key_comp(p->forward[i]->key, key) < 0) {
            p = p->forward[i]; 
        }
        update[i] = p;
    }

    p = p->forward[0];
    if(p == NULL || skp->type.key_comp(p->key, key) != 0)
        return; 

    for(int i = 0; i < skp->cur_level; ++i) {
        if(update[i]->forward[i] != p) 
            break;

        update[i]->forward[i] = p->forward[i];
    }

    skp->type.key_desc(p->key);
    skp->type.val_desc(p->val);
    free(p);

    while(skp->cur_level > 0 && skp->head.forward[skp->cur_level - 1] == NULL) {
        --skp->cur_level;
    }
    --skp->cur_nodes;
} 

void skp_destroy(skiplist *skp) {
    listnode *p = skp->head.forward[0];
    while(p) {
         listnode *next = p->forward[0];

         skp->type.key_desc(p->key);
         skp->type.val_desc(p->val);
         free(p);

         p = next;
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
