#include "shell.h"

/**
 * execve_command - handles execution
 *
 * @args: argument passed
 */

void execve_command(char **args)
{
	execve(args[0], args, NULL);
	perror("execve error");
	_exit(EXIT_FAILURE);
}

/**
 * update_fd_prev - handles fd
 *
 * @fd_prev: arg 1
 * @fd_current: arg 2
 * @i: for count
 */

void update_fd_prev(int fd_prev[2], int fd_current[2], int i)
{
	if (i != 0)
	{
		close(fd_prev[0]);
		close(fd_prev[1]);
	}
	fd_prev[0] = fd_current[0];
	fd_prev[1] = fd_current[1];
}

/**
 * close_fd_prev - close fd
 *
 * @fd_prev: fd used
 */

void close_fd_prev(int fd_prev[2])
{
	if (fd_prev[0] != -1)
		close(fd_prev[0]);
	if (fd_prev[1] != -1)
		close(fd_prev[1]);
}

/**
 * wait_for_children - hanles parent process
 *
 * @num_commands: num commands
 */

void wait_for_children(int num_commands)
{
	int i;

	for (i = 0; i < num_commands; i++)
		wait(NULL);
}

/**
 * execute_piped_commands - handles pipe
 *
 * @commands: passed arguments
 *
 */

void execute_piped_commands(char ***commands)
{
	int num_commands = 0, i, fd_prev[2] = {-1, -1};
	pid_t pid;

	while (commands[num_commands] != NULL)
		num_commands++;
	for (i = 0; i < num_commands; i++)
	{
		int fd_current[2];

		if (pipe(fd_current) == -1)
		{
			perror("pipe error");
			_exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				dup2(fd_prev[0], STDIN_FILENO);
				close(fd_prev[0]);
				close(fd_prev[1]);
			}
			if (i != num_commands - 1)
			{
				close(fd_current[0]);
				dup2(fd_current[1], STDOUT_FILENO);
				close(fd_current[1]);
			}
			execve_command(commands[i]);
		} else if (pid < 0)
		{
			perror("fork error");
			_exit(EXIT_FAILURE);
		} else
			update_fd_prev(fd_prev, fd_current, i);
	}
	close_fd_prev(fd_prev);
	wait_for_children(num_commands);
}
