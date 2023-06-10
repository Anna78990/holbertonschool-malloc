#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int32_t has_initialized = 0;
MemChunkHeader top_header = {0, NULL};
void *last_valid_address;
void *managed_memory_start;

/**
 * smalloc_init - initialize malloc setting
 *
 * Return: always nothing
 */
void smalloc_init(void)
{
	last_valid_address = sbrk(0);
	managed_memory_start = last_valid_address;
	has_initialized = 1;
}

/**
 * smalloc_brk - allocate memory of given byte number
 *
 * @numbytes: number of byte
 *
 * Return: pointer to address
 */
void *smalloc_brk(size_t numbytes)
{
	void *current_location;
	MemControlBlock *current_location_mcb;
	void *memory_location;

	numbytes = numbytes + sizeof(MemControlBlock);
	memory_location = 0;
	current_location = managed_memory_start;
	if (numbytes > HEAP_MAX)
		return (NULL);
	while (current_location != last_valid_address)
	{
		current_location_mcb = (MemControlBlock *)current_location;
		if (current_location_mcb->is_available)
		{
			if ((size_t)current_location_mcb->size >= numbytes)
			{
				current_location_mcb->is_available = 0;
				memory_location = current_location;
				break;
			}
		}
		current_location = (void *)((char *)current_location +
				current_location_mcb->size);
	}
	if (!memory_location)
	{
		if (numbytes > ((size_t) managed_memory_start +
				(size_t)HEAP_MAX - (size_t)last_valid_address))
			return (NULL);
		if (sbrk(numbytes) == (void *) -1)
			return (NULL);
		memory_location = last_valid_address;
		last_valid_address = (void *)((char *)last_valid_address + numbytes);
		current_location_mcb = memory_location;
		current_location_mcb->is_available = 0;
		current_location_mcb->size = numbytes;
	}
	memory_location = (void *)((char *)memory_location +
			sizeof(MemControlBlock));
	return (memory_location);
}

/**
 * _malloc - malloc
 *
 * @size: size of byte to allocate
 *
 * Return: pointer to address
 */
void *_malloc(size_t size)
{
	void *smalloc_brk_result;
	void *smalloc_result;
	MemChunkHeader *p_chunk_header;

	if (!has_initialized)
		smalloc_init();
	if (!size)
		return (NULL);
	smalloc_brk_result = smalloc_brk(size);
	if (smalloc_brk_result)
		return (smalloc_brk_result);
	size = size + sizeof(MemChunkHeader);
	p_chunk_header = &top_header;
	while (p_chunk_header->next)
		p_chunk_header = p_chunk_header->next;
	smalloc_result = mmap(NULL, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!smalloc_result)
		return (NULL);
	p_chunk_header->next = smalloc_result;
	((MemChunkHeader *)smalloc_result)->next = NULL;
	((MemChunkHeader *)smalloc_result)->size = size;
	smalloc_result = (void *)((char *)smalloc_result + sizeof(MemChunkHeader));
	return (smalloc_result);
}
