#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *_malloc(size_t size);
void _free(void *ptr);
void *_realloc(void *ptr, size_t size);

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
    char *str;
    int i;
    void *chunk;

    printf("Starting break is %p\n", sbrk(0));

    str = _malloc(10);
    strcpy(str, "Holberton");
    str[9] = '\0';
    printf("%p: %s, ", (void *)str, str);
    chunk = (void *)(str - sizeof(size_t));
    printf("chunk starting at address %p, ", (void *)chunk);
    _realloc(str, 20);
    chunk = (void *)(str - sizeof(size_t));
    printf("chunk size is %lu\n", *((size_t *)chunk));
    _free(str);

    printf("Final break is %p\n", sbrk(0));
    return (EXIT_SUCCESS);
}
