#include <unistd.h>
#include <stddef.h>
#include "malloc.h"

static MemChunkHeader *first_chunk;
static size_t chunk_count;

/**
 * naive_malloc - allocate memory
 * @size: size to allocate
 * Return: pointer to allocated memory
 */
void *naive_malloc(size_t size)
{
	size_t total_size;
	MemChunkHeader *current_chunk, *new_chunk;

	if (first_chunk == NULL)
	{
		new_chunk = sbrk(PAGE_SIZE);
		if (new_chunk == (void *)-1)
			return (NULL);
		new_chunk->size = PAGE_SIZE - sizeof(MemChunkHeader);
		new_chunk->next = NULL;
		first_chunk = new_chunk;
		chunk_count++;
	}

	current_chunk = first_chunk;
	while (current_chunk != NULL)
	{
		if (current_chunk->size >= size)
		{
			total_size = size + sizeof(MemChunkHeader);
			if (current_chunk->size >= total_size)
			{
				new_chunk = (MemChunkHeader *)((char *)current_chunk
						+ total_size);
				new_chunk->size = current_chunk->size - total_size;
				new_chunk->next = current_chunk->next;
				current_chunk->size = size;
				current_chunk->next = new_chunk;
			}
			return ((void *)(current_chunk + 1));
		}
		current_chunk = current_chunk->next;
	}
	new_chunk = sbrk(PAGE_SIZE);
	if (new_chunk == (void *)-1)
		return (NULL);
	new_chunk->size = PAGE_SIZE - sizeof(MemChunkHeader);
	new_chunk->next = NULL;
	chunk_count++;
	return (naive_malloc(size));
}
