#include "shell.h"

/**
 * shell_cd - Implementation of the cd command.
 * @args: Array of command arguments.
 * Return: 1 on success, 0 on failure.
 */
int shell_cd(char **args)
{
	char *home_dir = getenv("HOME");
	char *target_dir = args[1];

	if (target_dir == NULL || *target_dir == '\0')
	{
		/* If no argument provided, change to the home directory */
		if (chdir(home_dir) != 0)
		{
			perror("cd");
			return 0;
		}
	}
	else
	{
		if (chdir(target_dir) != 0)
		{
			perror("cd");
			return 0;
		}
	}

	return 1; /* Indicate successful execution of the command */
}

