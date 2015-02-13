#ifndef __MAP_H__
#define __MAP_H__

typedef struct htable_s htable_t;

struct htable_s {
     
};

htable_t *htable_create();
void htable_destroy(htable_t *ht);
int htable_insert(htable_t *ht, int key, int val);
int htable_find(htable_t *ht, int key, int *val);
int htable_delete(htable_t *ht, int key);


#endif
