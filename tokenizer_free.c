#include "shell.h"

/**
 * free_tokenized_piped_commands - free memory of piped commands
 *
 * @commands: everything passed
 */

void free_tokenized_piped_commands(char ***commands)
{
	int i;

	if (commands == NULL)
		return;
	for (i = 0; commands[i] != NULL; i++)
		free_tokenized_command(commands[i]);
	free(commands);
}

/**
 * free_tokenized_command - free command not passed with pipe
 *
 * @args: command line argument
 */

void free_tokenized_command(char **args)
{
	int i;

	if (args == NULL)
		return;
	for (i = 0; args[i] != NULL; i++)
		free(args[i]);
	free(args);
}
