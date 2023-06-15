#include "malloc.h"

/**
 * _calloc - allocate memories and set 0 to all of the memories
 * @nmemb: number of memory
 * @size: size of memory
 * Return: always nothing
 */
void *_calloc(size_t nmemb, size_t size)
{
	void *pmem;

	pmem = _malloc(nmemb * size);
	if (!pmem)
		return (NULL);
	memset(pmem, 0, nmemb * size);
	return (pmem);
}
