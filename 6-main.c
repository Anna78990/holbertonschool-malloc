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
    char *str;
    void *chunk;
    int *a;

    printf("Starting break is %p\n", sbrk(0));

    str = _malloc(10);
    strcpy(str, "Holberton");
    str[9] = '\0';
    printf("%p: %s, ", (void *)str, str);
    chunk = (void *)(str - sizeof(size_t));
    printf("chunk starting at address %p, ", (void *)chunk);
    chunk = (void *)(str - sizeof(size_t));
    printf("chunk size is %lu\n", *((size_t *)chunk));
    _free(str);
    a = (int *)_calloc(5, sizeof(int));
    a[1] = 1;
    printf("a[0] is %d\n", a[0]);
    printf("a[1] is %d\n", a[1]);
    printf("Final break is %p\n", sbrk(0));
    return (EXIT_SUCCESS);
}
