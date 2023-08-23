#include "shell.h"

/**
 * main - Simple shell command line interpreter
 *
 * Return: Always 0.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        printf("#cisfun$ "); // Display the prompt

        // Read user input
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (feof(stdin)) // Check for EOF (Ctrl+D)
            {
                printf("\n");
                break;
            }
            perror("getline error");
            exit(EXIT_FAILURE);
        }

        // Remove newline character from input
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the input
        char **args = tokenizer(line);

        // Execute the command
        execute(args);

        // Free allocated memory
        free_tokenized_command(args);
    }

    // Free allocated memory
    free(line);

    return 0;
}

