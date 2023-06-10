#include "malloc.h"

/**
 * _realloc - reallocate the memory to given address
 * @ptr: pointer to the existed memory to add
 * @size: size of memory to allocate
 * Return: always nothing
 */
void *_realloc(void *ptr, size_t size)
{
	void *dst;
	void *p;
	size_t src_size;

	if (ptr >= managed_memory_start && ptr <= last_valid_address)
	{
		p = ptr - sizeof(MemControlBlock);
		src_size = ((MemControlBlock *)p)->size - sizeof(MemControlBlock);
	}
	else
	{
		p = ptr - sizeof(MemChunkHeader);
		src_size = ((MemChunkHeader *)p)->size - sizeof(MemChunkHeader);
	}
	if (size <= src_size)
		return (ptr);
	dst = _malloc(size);
	if (!dst)
		return (NULL);
	memcpy(dst, ptr, src_size);
	_free(ptr);
	return (dst);
}
