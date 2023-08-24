#include "shell.h"

/**
 * trim_whitespace - handles excessive white space in command
 *
 * @str: sring considered
 *
 * Return: strimmed string
 */

char *trim_whitespace(const char *str)
{
	const char *end;
	size_t trimmed_length;
	char *trimmed_str;

	while (isspace(*str))
	{
		str++;
	}
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
	{
		end--;
	}
	trimmed_length = end - str + 1;
	trimmed_str = malloc(trimmed_length + 1);
	if (trimmed_str == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	memcpy(trimmed_str, str, trimmed_length);
	trimmed_str[trimmed_length] = '\0';
	return (trimmed_str);
}
