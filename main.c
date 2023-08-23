#include "shell.h"

/**
 * main - Custom Shell
 *
 * Return: 0 on success
 */

int main(void)
{
	char *buffer = NULL;
	size_t buffer_size = 1024;
	ssize_t get;
	char *input;
	char **args;
	char ***commands;

	while (1)
	{
		write(1, "Tim and OLa Shell$ ", 19);
		get = getline(&buffer, &buffer_size, stdin);
		if (get == -1)
		{
			perror("getline error");
			free(buffer);
			return (1);
		}
		if (buffer[get - 1] == '\n')
			buffer[get - 1] = '\0';
		input = buffer;
		if (strcmp(buffer, "exit") == 0)
			break;
		if (strchr(input, '|') != NULL)
		{
			commands = tokenize_piped_commands(input);
			execute_piped_commands(commands);
			free_tokenized_piped_commands(commands);
		}
		else
		{
			args = tokenizer(input);
			execute(args);
			free(args);
		}
	}
	free(buffer);
	return (0);
}
