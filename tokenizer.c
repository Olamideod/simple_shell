#include "shell.h"

/**
 * tokenizer - tokenizes passed command
 *
 * @input: command passed
 *
 * Return: array
 */

char **tokenizer(const char *input)
{
	char **args;
	int arg_count = 0;
	char *token;

	args = malloc(sizeof(char *) * (MAX_ARGUMENTS + 1));
	if (args == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	token = strtok((char *)input, " ");
	while (token != NULL && arg_count < MAX_ARGUMENTS)
	{
		args[arg_count++] = strdup(token);
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	return (args);
}
