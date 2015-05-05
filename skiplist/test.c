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

    for(int i = 0; i < 20; i += 3) {
        int *key = (int *)malloc(sizeof(int));
        *key = i;

        char *val = (char *)malloc(100);
        snprintf(val, 100, "key is %d", i);

        skp_insert(skp, key, val);
    }
    
    int key = -1;
    listnode *node = skp_search(skp, &key);
    if(node) {
        printf("key=%d, val=%s\n", *((int *)node->key), (char *)node->val);
    } else {
        printf("key=%d not found!\n", key);
    }

    key = 3;
    node = skp_search(skp, &key);
    if(node) {
        printf("key=%d, val=%s\n", *((int *)node->key), (char *)node->val);
    } else {
        printf("key=%d not found!\n", key);
    }

    key = 5;
    node = skp_search(skp, &key);
    if(node) {
        printf("key=%d, val=%s\n", *((int *)node->key), (char *)node->val);
    } else {
        printf("key=%d not found!\n", key);
    }

    key = 18;
    node = skp_search(skp, &key);
    if(node) {
        printf("key=%d, val=%s\n", *((int *)node->key), (char *)node->val);
    } else {
        printf("key=%d not found!\n", key);
    }
    
    key = 25;
    node = skp_search(skp, &key);
    if(node) {
        printf("key=%d, val=%s\n", *((int *)node->key), (char *)node->val);
    } else {
        printf("key=%d not found!\n", key);
    }

    printf("-------cur_nodes=%d\n", skp->cur_nodes);
    key = 3;
    skp_delete(skp, &key);
    printf("-------delete 3, cur_nodes=%d\n", skp->cur_nodes);
    key = 18;
    skp_delete(skp, &key);
    printf("-------delete 18, cur_nodes=%d\n", skp->cur_nodes);
    key = 9;
    skp_delete(skp, &key);
    printf("-------delete 9, cur_nodes=%d\n", skp->cur_nodes);
    key = -1;
    skp_delete(skp, &key);
    key = 25;
    skp_delete(skp, &key);

    printf("----------after delete------------\n");
    
    key = 3;
    node = skp_search(skp, &key);
    if(node) {
        printf("key=%d, val=%s\n", *((int *)node->key), (char *)node->val);
    } else {
        printf("key=%d not found!\n", key);
    }

    key = 9;
    node = skp_search(skp, &key);
    if(node) {
        printf("key=%d, val=%s\n", *((int *)node->key), (char *)node->val);
    } else {
        printf("key=%d not found!\n", key);
    }

    key = 18;
    node = skp_search(skp, &key);
    if(node) {
        printf("key=%d, val=%s\n", *((int *)node->key), (char *)node->val);
    } else {
        printf("key=%d not found!\n", key);
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
