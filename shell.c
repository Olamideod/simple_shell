#include "shell.h"

/**
 * execute - runs command
 *
 * @input: command line argument
 *
 * Return: integer value
 */

int execute(char **input)
{
	pid_t pid;
	int stat;
	char *envp[] = {NULL};

	pid = fork();
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

/**
 * tokenize_piped_commands - handles piped commands
 *
 * @input: command to be tokenized
 *
 * Return: tokenized array of strings
 */

char ***tokenize_piped_commands(const char *input)
{
	char ***commands = NULL;
	int command_count = 0;
	char *input_copy;
	char *token;

	input_copy = strdup(input);
	if (input_copy == NULL)
	{
		perror("strdup error");
		exit(EXIT_FAILURE);
	}
	token = strtok(input_copy, "|");
	while (token != NULL)
	{
		token = trim_whitespace(token);
		if (strlen(token) > 0)
		{
			commands = realloc(commands, sizeof(char **) * (command_count + 2));
			if (commands == NULL)
			{
				perror("realloc error");
				exit(EXIT_FAILURE);
			}
			commands[command_count] = tokenizer(token);
			commands[command_count + 1] = NULL;
			command_count++;
		}
		token = strtok(NULL, "|");
	}
	free(input_copy);
	return (commands);
}

/**
 * tokenizer - tokenizes input
 *
 * @input: command line argument
 *
 * Return: tokenized array of strings
 */

char **tokenizer(const char *input)
{
	char **args;
	int arg_count = 0;
	char *token;

	args = malloc(sizeof(char *) * (MAX_ARGUMENTS + 1));
	if (args == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	token = strtok((char *)input, " ");
	while (token != NULL && arg_count < MAX_ARGUMENTS)
	{
		args[arg_count++] = strdup(token);
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;
	return (args);
}

/**
 * trim_whitespace - handles excessive white space in command
 *
 * @str: sring considered
 *
 * Return: strimmed string
 */

char *trim_whitespace(const char *str)
{
	const char *end;
	size_t trimmed_length;
	char *trimmed_str;

	while (isspace(*str))
	{
		str++;
	}
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
	{
		end--;
	}
	trimmed_length = end - str + 1;
	trimmed_str = malloc(trimmed_length + 1);
	if (trimmed_str == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	memcpy(trimmed_str, str, trimmed_length);
	trimmed_str[trimmed_length] = '\0';
	return (trimmed_str);
}
