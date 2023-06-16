#ifndef MALLOC_H
#define MALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define HEAP_MAX (1024 * 10)

#define PAGE_SIZE 4096

/**
 * struct MemChunkHeader - chunk of malloced memory
 *
 * @size: size of allocated memory
 * @next: next memory adress
 */
typedef struct MemChunkHeader
{
	size_t size;
	struct MemChunkHeader *next;
} MemChunkHeader;

/**
 * struct MemControlBlock - structure for check if memory is available
 *
 * @is_available: check if it is available
 * @size: size of memory block
 */
typedef struct MemControlBlock
{
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
void *_realloc(void *ptr, size_t size);
void *_calloc(size_t nmemb, size_t size);

#endif
