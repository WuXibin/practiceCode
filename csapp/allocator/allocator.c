#include "allocator.h"
#include <stdio.h>

#define HEADER_SIZE 4
#define ALIGN_MASK  8

#define ALIGN(x,a)              __ALIGN_MASK(x,(typeof(x))(a)-1)
#define __ALIGN_MASK(x,mask)    (((x)+(mask))&~(mask))

#define BLOCK_GET_SIZE(x) (*x & ~(ALIGN_MASK - 1))
#define BLOCK_GET_BIT(x) (*x & 1)
#define BLOCK_NEXT(x) ((x) + (BLOCK_GET_SIZE(x) >> 2)) 
#define BLOCK_END(x) (*x == 1)

#define REQUEST_SIZE(x) ALIGN(__REQUEST_SIZE(x), ALIGN_MASK)
#define __REQUEST_SIZE(x) ((x) + (HEADER_SIZE << 1))

static void* gHeapEntry = NULL;

static void* csapp_find_space(size_t);
static void csapp_split_block(void*, size_t);
static void* csapp_new_space(size_t);
static void csapp_free_space(void*);
static void csapp_merge_(void*, void*);
static void csapp_merge_space(void*); 


void* csapp_malloc(size_t nmemb) {
    void* block = csapp_find_space(nmemb);
    if(block)
        return block;
    return csapp_new_space(nmemb); 
}

void csapp_free(void *address) {
    csapp_free_space(address);    
}

static void* csapp_find_space(size_t nbytes) {
    int *block = (int *)gHeapEntry + 1;
    int nsize = REQUEST_SIZE(nbytes);
    while(!BLOCK_END(block)) {
        if(!BLOCK_GET_BIT(block) && BLOCK_GET_SIZE(block) >= nsize) {
            csapp_split_block(block, nsize);
            return block;         
        }
        block = BLOCK_NEXT(block);
    }    
    return NULL;
}

static void csapp_split_block(void *block, size_t nbytes) {
    int *block_head = (int *)block;
    int *next_head;
    size_t nsize = BLOCK_GET_SIZE(block_head);
    if(nsize - nbytes > (HEADER_SIZE << 1)) {
        *block_head = nsize | 0x1;
        next_head = BLOCK_NEXT(block_head);
        *(next_head - 1) = *block_head;
        *next_head = nsize - nbytes; 
    } else {
        *block_head |= 0x1;
    }
}

static void* csapp_new_space(size_t nbytes) {
    void* heap_top;
    int* block_head;
    int nsize = REQUEST_SIZE(nbytes);
    if(!gHeapEntry) {
        heap_top = sbrk(ALIGN(HEADER_SIZE << 1, ALIGN_MASK));
        if(heap_top == (void*)-1) {
            perror("sbrk error");
            return NULL;
        } 
        block_head = (int*)heap_top;
        *block_head++ = 0x1;
        *block_head = 0x1;
        gHeapEntry= heap_top;
    }    
    
    heap_top = sbrk(ALIGN(nsize, ALIGN_MASK));
    if(heap_top == (void*)-1) {
        perror("sbrk error");
        return NULL;
    }
    block_head = (int*)heap_top - 1;
    *block_head = nsize | 0x1;
    block_head = BLOCK_NEXT(block_head);
    *(block_head - 1) = *block_head;
    *block_head = 0x1;
    
    return heap_top;
}

static void csapp_free_space(void* address) {
    int *block_head = (int *)address - 1;
    int *block_tail;
    size_t nsize = BLOCK_GET_SIZE(block_head);
    
    *block_head = nsize;
    block_tail = BLOCK_NEXT(block_head) - 1;
    *block_tail = nsize;
    csapp_merge_space(block_head);
}

static void csapp_merge_space(void *address) {
    int *curr_block = (int *)address;
    int *prev_block = curr_block - 1;
    int *next_block = curr_block + (*curr_block >> 2);
    if(*prev_block & 0x1) {
        prev_block -= (*prev_block >> 2) - 1;
        csapp_merge_(prev_block, curr_block);
    }
    if(*next_block & 0x1)
        csapp_merge_(prev_block, next_block);
}

static void csapp_merge_(void *first_block, void *second_block) {
    int *first_head = (int *)first_block;
    int *second_head = (int *)second_block;
    int *block_tail;

    *first_head += *second_head;
    block_tail = first_head + (*first_head >> 2) - 1;
    *block_tail = *first_head; 
}
