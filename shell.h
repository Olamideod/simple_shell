#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_ARGUMENTS 32

int execute(char **input);
void execute_piped_commands(char ***commands);
void free_tokenized_piped_commands(char ***commands);
void free_tokenized_command(char **args);
char ***tokenize_piped_commands(const char *input);
char **tokenizer(const char *input);
char *trim_whitespace(const char *str);
void execve_command(char **args);
void update_fd_prev(int fd_prev[2], int fd_current[2], int i);
void close_fd_prev(int fd_prev[2]);
void wait_for_children(int num_commands);

#endif
