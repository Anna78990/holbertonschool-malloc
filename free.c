#include "malloc.h"

void *managed_memory_start;
void *last_valid_address;
MemChunkHeader top_header;

/**
 * free_brk - free break point
 *
 * @ptr: pointer to memory
 */
void free_brk(void *ptr)
{
	void *p;
	MemControlBlock *mcb;
	size_t acc_empty = 0;

	mcb = (void *)((char *)ptr - sizeof(MemControlBlock));
	mcb->is_available = 1;
	p = managed_memory_start;
	for ( ; p != last_valid_address; p = (void *)((char *)p + mcb->size))
	{
		mcb = (MemControlBlock *)p;
		if (mcb->is_available)
			acc_empty = acc_empty + mcb->size;
		else
			acc_empty = 0;
	}
	if (acc_empty > 0)
	{
		sbrk(0 - acc_empty);
		last_valid_address = sbrk(0);
	}
}

/**
 * _free - free allocated memories
 * @ptr: pointer to the given memories
 */
void _free(void *ptr)
{
	MemChunkHeader *p;
	MemChunkHeader *tmp;

	if (!ptr)
		return;
	if (ptr >= managed_memory_start && ptr <= last_valid_address)
	{
		free_brk(ptr);
		return;
	}
	p = &top_header;
	while ((void *)((char *)(p->next) + sizeof(MemChunkHeader)) != ptr)
		p = p->next;
	tmp = (p->next)->next;
	munmap(p->next, (p->next)->size);
	p->next = tmp;
}
