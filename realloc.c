#include "malloc.h"

/**
 * _realloc - allocate the memory and add to existed memory
 * @ptr: pointer to the existed memory to add
 * @size: size of memory to allocate
 * Return: always nothing
 */
void *_realloc(void *ptr, size_t size)
{
	void *dst;
	void *p;
	size_t src_size;

	if (src >= managed_memory_start && src <= last_valid_address)
	{
		p = src - sizeof(MemControlBlock);
		src_size = ((MemControlBlock *)p)->size - sizeof(MemControlBlock);
	}
	else
	{
		p = src - sizeof(MemChunkHeader);
		src_size = ((MemChunkHeader *)p)->size - sizeof(MemChunkHeader);
	}
	if (size <= src_size)
		return (src);
	dst = smalloc(size);
	if (!dst)
		return (NULL);
	memcpy(dst, src, src_size);
	free(src);
	return (dst);
}
