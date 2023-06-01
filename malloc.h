#ifndef MALLOC_H
#define MALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define HEAP_MAX 1024*10

typedef struct MemChunkHeader{
    size_t size;
    struct MemChunkHeader *next;
} MemChunkHeader;

typedef struct MemControlBlock { 
    int32_t is_available; 
    int32_t size;
} MemControlBlock;

extern int32_t has_initialized;
extern void *managed_memory_start;
extern void *last_valid_address;
extern MemChunkHeader top_header;

void malloc_init(void);
void *naive_malloc(size_t size);
void *_malloc(size_t size);
void _free(void *ptr);

#endif
