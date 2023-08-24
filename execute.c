#include "shell.h"

/**
 * execute - executes commands
 *
 * @input: command passed
 *
 * Return: exit
 */

int execute(char **input)
{
	pid_t pid = fork();
	int exit_status;
	char *envp[] = {NULL};

	if (pid == 0)
	{
		execve(input[0], input, envp);
		perror("execve error");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork error");
		exit_status = 1;
	}
	else
	{
		wait(&exit_status);
	}
	return (exit_status);
}
