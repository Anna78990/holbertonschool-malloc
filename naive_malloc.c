#include <unistd.h>
#include <stddef.h>
#include "malloc.h"

static void *first_chunk;
static size_t chunk_count;

/**
 * align - get the size for alignment
 * @size: size to allocate
 * Return: size for alignment
 */
size_t align(size_t size)
{
	return ((size + (16 - (size % 16))));
}

/**
 * _naive_malloc - create pages
 * @page: Variable to store page number
 *
 * Return: A pointer to the pages
 */
void *_naive_malloc(ssize_t *page)
{
	void *first_chunk;

	(*page) = sysconf(_SC_PAGESIZE);
	if ((*page) == -1)
		return (NULL);
	first_chunk = sbrk((*page));
	if (first_chunk == (void *)-1)
		return (NULL);
	return (first_chunk);
}


/**
 * naive_malloc - Allocate enough memory to store
 * @size: Is the size needed to be allocated for the user
 *
 * Return: A pointer to the allocated memory that is suitably aligned
 * for any kind of variable
 */
void *naive_malloc(size_t size)
{
	void *ptr, *next_block = NULL;
	size_t block = align(size) + sizeof(size), i, block_size, temp;
	ssize_t page;

	if (!chunk_count)
	{
		first_chunk = _naive_malloc(&page);
		if (!first_chunk)
			return (NULL);
	}
	for (i = 0, ptr = first_chunk; i < chunk_count; i++)
	{
		block_size = *(size_t *)ptr;
		ptr = (char *)ptr + block_size;
	}
	if (chunk_count)
		temp = *(size_t *)ptr;
	else
		temp = (size_t)page;
	next_block = ((char *)ptr) + block;
	while (temp < (sizeof(size) * 2) + align(size))
	{
		first_chunk = _naive_malloc(&page);
		if (!first_chunk)
			return (NULL);
		temp += page;
	}
	*(size_t *)next_block = temp - block;
	*(size_t *)ptr = block;
	chunk_count++;
	return ((char *)ptr + sizeof(size));
}
