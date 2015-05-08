#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#define MaxLevel    16
#define Fraction    50          /* percentage */

typedef int (*KeyCompare)(void *, void *);
typedef void (*Destructor)(void *);

typedef struct skiptype {
    KeyCompare key_comp;
    Destructor key_desc;
    Destructor val_desc;
} skiptype;

typedef struct listnode {
    void *key;
    void *val;
    struct listnode *forward[MaxLevel];
} listnode;

typedef struct skiplist {
    int cur_nodes;
    int cur_level;
    skiptype type;
    listnode head;
} skiplist;

skiplist* skp_create(skiptype type);
listnode* skp_search(skiplist *skp, void *key);
void skp_insert(skiplist *skp, void *key, void *data);
void skp_delete(skiplist *skp, void *key);
void skp_destroy(skiplist *skp);

#endif
