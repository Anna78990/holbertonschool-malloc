#include <unistd.h>

typedef struct block {
    size_t size;
    struct block* next;
} block_t;

void *naive_malloc(size_t size)
{
    size_t total_size = sizeof(block_t) + size;

    // Allocate memory using sbrk
    void *ptr = sbrk(total_size);
    if (ptr == (void *)-1) {
        return NULL;
    }

    // Create a block structure at the beginning of the allocated memory
    block_t *block = (block_t *)ptr;
    block->size = size;

    // Calculate the user pointer
    void *user_ptr = (void *)((char *)ptr + sizeof(block_t));

    return user_ptr;
}
