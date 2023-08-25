#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *original_dest = dest;

	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */

char *_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == NULL)
		return (dest);
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return dest;
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (0);
	while (str[length])
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (0);
	for (int i = 0; i <= length; i++)
		result[i] = str[i];
	return result;
}
