#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer Sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command Chaining Types */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Conversion Flags for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* Flag for using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains pseudo-arguments for functions
 * @arg: Argument string generated from getline
 * @argv: Array of strings generated from arg
 * @path: String path for the current command
 * @argc: Argument count
 * @line_count: Error count
 * @err_num: Error code for exit()s
 * @linecount_flag: If on, count this line of input
 * @fname: Program filename
 * @env: Linked list local copy of environ
 * @environ: Custom modified copy of environ from LL env
 * @history: History node
 * @alias: Alias node
 * @env_changed: On if environ was changed
 * @status: Return status of the last exec'd command
 * @cmd_buf: Address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: Command type (||, &&, ;)
 * @readfd: File descriptor for reading line input
 * @histcount: History line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* Pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* Command type: ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Structure that contains built-in commands and their handlers
 * @type: The flag indicating the built-in command type
 * @func: The corresponding function to handle the command
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* Command Loop Functions */
int execute_shell(info_t *, char **);
int search_builtin(info_t *);
void locate_command(info_t *);
void execute_forked_command(info_t *);

/* Command Parser */
int check_command(info_t *, char *);
char *copy_characters(char *, int, int);
char *find_command_path(info_t *, char *, char *);

/* Command Execution */
int initiate_command(info_t *, char **);

/* Error Handling Functions */
void display_error_output(char *);
int print_error_char(char);
int write_to_file(char c, int fd);
int print_to_fd_with_string(char *str, int fd);

/* String Manipulation */
int length_of_string(char *);
int compare_text(char *, char *);
char *identify_substring(const char *, const char *);
char *combine_strings_in_order(char *, char *);

/* String Manipulation Part 1 */
char *copy_string_content(char *, char *);
char *replicate_string(const char *);
void show_string(char *);
int output_char(char);

/* Exiting with Control */
char *copy_part_of_string(char *, char *, int);
char *append_substring(char *, char *, int);
char *search_character(char *, char);

/* Tokenization of Input */
char **divide_string(char *, char *);
char **split_string_with_delimiter(char *, char);

/* Dynamic Memory Reallocation */
char *fill_with_character(char *, char, unsigned int);
void release_memory(char **);
void *resize_allocation(void *, unsigned int, unsigned int);

/* Dynamic Memory Management */
int free_allocated_memory(void **);

/* Conversion from String to Integer */
int interactive_input(info_t *);
int check_delimiter(char, char *);
int check_alphabetical_character(int);
int convert_to_integer(char *);

/* Handling Error Scenarios */
int convert_to_int_with_error_handling(char *);
void indicate_error(info_t *, char *);
int output_decimal(int, int);
char *transform_number(long int, int, int);
void delete_comments(char *);

/* Implementation of Builtin Commands */
int terminate_shell(info_t *);
int change_directory(info_t *);
int provide_assistance(info_t *);

/* Additional Builtin Commands */
int display_shell_history(info_t *);
int manage_command_aliases(info_t *);

/* Reading User Input */
ssize_t retrieve_user_input(info_t *);
int acquire_input(info_t *, char **, size_t *);
void interrupt_handler(int);

/* Retrieving Shell Information */
void clear_shell_info(info_t *);
void set_shell_info(info_t *, char **);
void release_shell_info(info_t *, int);

/* Handling Environment Variables */
char *access_environment(info_t *, const char *);
int manage_environment(info_t *);
int adjust_environment(info_t *);
int unset_environment_variable(info_t *);

/* Manipulating Environment Variables */
char **access_environment_variables(info_t *);
int delete_environment_variable(info_t *, char *);
int establish_environment_variable(info_t *, char *, char *);

/* Management of Command History */
char *get_history_file_path(info_t *info);
int record_command_history(info_t *info);
int load_command_history(info_t *info);
int construct_history_list(info_t *info, char *buf, int linecount);
int reorder_command_history(info_t *info);

/* Manipulating Linked Lists */
list_t *insert_node_at_beginning(list_t **, const char *, int);
list_t *insert_node_at_end(list_t **, const char *, int);
size_t display_string_list(const list_t *);
int remove_node_at_index(list_t **, unsigned int);
void clear_linked_list(list_t **);

/* Working with Linked Lists - Part 1 */
size_t calculate_list_length(const list_t *);
char **convert_list_to_strings(list_t *);
size_t display_list_contents(const list_t *);
list_t *find_node_starting_with(list_t *, char *, char);
ssize_t get_index_of_node(list_t *, list_t *);

/* Managing Variables */
int determine_chaining(info_t *, char *, size_t *);
void verify_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_with_alias(info_t *);
int substitute_variables(info_t *);
int swap_string(char **, char *);

#endif

