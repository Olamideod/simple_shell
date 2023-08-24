#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_ARGUMENTS 32

// Tokenizer function without using strtok
char **tokenizer(const char *input);

// Execute a command
int execute(char **input);

// Built-in command handlers
int shell_cd(char **args);
int shell_exit(void);
int shell_env(char **envp);
int shell_setenv(char *args, char **envp);
int shell_unsetenv(char *args, char **envp);

// Advanced tasks functions
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
char **custom_tokenizer(const char *input);



// Task-specific built-in command handlers
int shell_alias(char **args);
int shell_variables(char **args);
int shell_file_input(char **args);

#endif
 
  
