#include "shell.h"

/**
 * shell_env - Implementation of the env command.
 * @envp: Array of environment variables.
 * Return: Always returns 1 to continue the shell loop.
 */
int shell_env(char **envp)
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		printf("%s\n", envp[i]);
	}

	return 1; /* Continue the shell loop */
}
