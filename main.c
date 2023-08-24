#include "shell.h"

/**
 * main - Custom Shell
 *
 * Return: 0 on success
 */

int main(void)
{
	char *buffer = NULL, *pipe_symbol;
	size_t buffer_size = 1024;
	ssize_t get;
	char **args;
	char ***commands;

	while (1)
	{
		write(1, "Tim and OLa Shell$ ", 19);
		get = getline(&buffer, &buffer_size, stdin);
		if (get == -1)
		{
			if (feof(stdin))
			{
				write(1, "\n", 1);
				break;
			}
			perror("getline error");
			free(buffer);
			_exit(1);
		}
		if (buffer[get - 1] == '\n')
			buffer[get - 1] = '\0';
		pipe_symbol = strchr(buffer, '|');
		if (pipe_symbol != NULL)
		{
			commands = tokenize_piped_commands(buffer);
			execute_piped_commands(commands);
			free_tokenized_piped_commands(commands);
		}
		else
		{
			args = tokenizer(buffer);
			execute(args);
			free(args);
		}
	}
	free(buffer);
	return (0);
}
