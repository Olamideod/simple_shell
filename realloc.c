#include "shell.h"

/**
 **_memset - Allocate memory with a const byte,
 *@s: The pointer to the allocated memory space,
 *@b: The byte to allocate *s with,
 *@n: The amount of bytes to be filled with,
 *Return: (s) the pointer to the memory space s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees the str of a str
 * @pp: str of a str.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - Reallocates a block of memory space,
 * @ptr: Pointer to the old allocated block space,
 * @old_size: byte size of the old block,
 * @new_size: byte size of a new block,
 *
 * Return: points to the old block name.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
