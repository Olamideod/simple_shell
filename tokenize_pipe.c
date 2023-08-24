#include "shell.h"

/**
 * tokenize_piped_commands - handles pipe
 *
 * @input: command passed
 *
 * Return: array
 */

char ***tokenize_piped_commands(const char *input)
{
	char ***commands = NULL;
	int command_count = 0;
	char *token;
	char *input_copy = strdup(input);

	if (input_copy == NULL)
	{
		perror("strdup error");
		exit(EXIT_FAILURE);
	}
	token = strtok(input_copy, "|");
	while (token != NULL)
	{
		token = trim_whitespace(token);
		if (strlen(token) > 0)
		{
			commands = realloc(commands, sizeof(char **) * (command_count + 2));
			if (commands == NULL)
			{
				perror("realloc error");
				exit(EXIT_FAILURE);
			}
			commands[command_count] = tokenizer(token);
			commands[command_count + 1] = NULL;
			command_count++;
		}
		token = strtok(NULL, "|");
	}
	free(input_copy);
	return (commands);
}

