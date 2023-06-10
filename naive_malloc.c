#include <unistd.h>

typedef struct block {
    size_t size;
    struct block* next;
} block_t;

/**
 * naive_malloc - naive malloc
 * @size: size of the memory to allocate
 */
void *naive_malloc(size_t size)
{
	size_t total_size = sizeof(block_t) + size;
	void *user_ptr;
	void *ptr = sbrk(total_size);
	block_t *block;

	if (ptr == (void *)-1)
		return NULL;

	block = (block_t *)ptr;
	block->size = size;

	user_ptr = (void *)((char *)ptr + sizeof(block_t));

	return user_ptr;
}
