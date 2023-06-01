#include "malloc.h"

#include <stddef.h>
#include <sys/mman.h>


struct page_header {
	size_t pages;
	size_t page_size;
	char page_data[]; //the rest of the page(s) of memory
};


static unsigned long get_page_size(void) {
	// initalize to invalid value
	static unsigned long page_size = 0;
	if (page_size == 0) {
		long tmp = sysconf(_SC_PAGESIZE);
		page_size = tmp < 0 ? 4096 : (unsigned long)tmp;
	}
	return page_size;
}


/** The simplest malloc()-ish function possible
 *
 *  Allocates the required number of pages of memory, places some header
 *  information at the start of the first page, then returns a pointer to the
 *  first byte after the header
 *  Allocates at least one page of memory for each call to simplify the logic
 *  Very inefficient for many small mallocs, but effective for one big malloc
 *  returns
 *   ________ _______ _______ ____     Page boundary
 *  | number |       |       |    |    |
 *  |   of   |data[0]|data[1]|... |    |
 *  | pages  |       |       |    |    |
 *   -------- ------- ------- ----
 *
 *  |--------|-------|
 *   size_t   sizeof(char)
 *           |--------------------|
 *            sizeof(char) * bytes
 */
static struct page_header* naive_malloc_internal(size_t size) {
	if (size == 0) {
		return NULL;
	}
	/* size in bytes of a page of memory */
	size_t page_size = get_page_size();
	/* size in bytes that needs to be allocated */
	size_t size_with_header = size + sizeof(struct page_header);
	/* number of pages to allocate */
	/* TODO: fix case where size_with_header == page_size */
	size_t pages = size_with_header / page_size + 1;
	size_t mmap_size = pages * page_size;
	void* ptr = mmap(0, mmap_size, PROT_READ|PROT_WRITE,
	MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED) {
		return NULL;
	}
	struct page_header* page = ptr;
	/* copy values to page header */
	page->pages = pages;
	page->page_size = page_size;
	return page;
}

void* naive_malloc(size_t size) {
	struct page_header* result = naive_malloc_internal(size);
	return result == NULL ? NULL : result->page_data;
}

