#include "shell.h"

/**
 * execute - function to execute command
 *
 * @input: command line argument
 *
 * Return: integer value
 */

int execute(char **input)
{
        pid_t pid = fork();
        int stat;
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
                return (1);
        }
        else
        {
                wait(&stat);
                return (WEXITSTATUS(stat));
        }
}



