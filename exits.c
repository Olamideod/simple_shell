#include "shell.h"

/**
 **_strncpy - Copy the str,
 *@dest: The destination str to copy to
 *@src: The source str,
 *@n: The amount of char to copy,
 *Return: The concatenated str.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - Concatenates the two str,
 *@dest: The first str,
 *@src: The second str,
 *@n: The amount of bytes to use maximally,
 *Return: The concatenated str.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - Find a char in the str,
 *@s: The str to be parsed,
 *@c: The char to locate,
 *Return: (s) the pointer to a memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
