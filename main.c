#include "shell.h"

/**
 * main - Entry point for the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        /* Display shell prompt */
        printf("$ ");
        /* Read user input */
        nread = custom_getline(&line, &len, stdin);

        if (nread == -1)
        {
            perror("getline error");
            break;
        }
        if (nread == 1)
            continue; /* Skip empty line */

        line[nread - 1] = '\0'; /* Remove newline character */

        /* Tokenize input */
        char **args = custom_tokenizer(line);
        if (args == NULL)
        {
            fprintf(stderr, "Tokenizer error\n");
            free(line);
            continue;
        }

        /* Execute command */
        int exit_status = execute(args);

        /* Free memory */
        free(line);
        for (int i = 0; args[i] != NULL; i++)
            free(args[i]);
        free(args);

        if (exit_status == -1)
        {
            perror("Execution error");
            break;
        }
    }

    free(line);

    return 0;
}
