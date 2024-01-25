#include <stdio.h>
#include <string.h>
#include "malloc.h"

char *test_malloc(size_t bytes)
{
	char *mal;
	char *success = "success!!";

	mal = (char *)_malloc(sizeof(char) * bytes);
	if (!mal)
		return (NULL);
	strcpy(mal, success);
	return (mal);
}

int main(void)
{
	char *mal;
	int *cal, i;

	mal = test_malloc(10);
	printf("mal = %s\n", mal);
	cal = _calloc(sizeof(int), 10);
	for (i = 0; i < 10; i++)
		if (cal[i] != 0)
			printf("Error: _calloc\n");
	printf("If there were not error alert, _calloc is succeeded.\n");
	_free(mal);
	_free(cal);
}


