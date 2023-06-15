#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "malloc.h"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	char *a, *b;

	a = (char *)_malloc(sizeof(char) * 10);
	printf("b = %p\n", (void *)a);
	b = _realloc(a, 3);
	printf("b = %p\n", (void *)b);
}
