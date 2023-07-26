#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdarg.h>
#include <limits.h>
#include <sys/stat.h>

#define MAX_ARGS 10
#define MAX_PATHS 10
#define PATH_MAX_LENGTH 100
#define READ_BUF_SIZE 1024

extern char **environ;

/**
 * struct shell_data - Shell data structure
 * @paths: Array of paths
 * @line: Pointer to the input line
 * @args: Array of arguments
 * @num_args: Number of arguments
 * @status: status of program
 * @program_name: name of program
 * @line_num: line number
 * @shell_exit_status: exit status of program
 */

typedef struct shell_data
{
	char *paths[MAX_PATHS];
	char *line;
	char *args[MAX_ARGS];
	int num_args;
	int status;
	char *program_name;
	int line_num;
	int shell_exit_status;
} shell_data;

char *get_path(struct shell_data *data, const char *command);
void tokenize(struct shell_data *data);
void print_env(void);
void free_shell_data(shell_data *data);
int read_shell_input(shell_data *data);
void init_shell_data(shell_data *data);
ssize_t _getline(shell_data *data);
void run_shell_command(shell_data *data);
void run_file_command(const char *program_name,
		const char *file_name, shell_data *data);
char *get_command_path(shell_data *data);
void wait_for_child(pid_t pid, int *status);
char *_strpbrk(const char *str, const char *accept);
int append_to_line(shell_data *data, char *input,
		ssize_t size, ssize_t *total_chars_read);
int execute_command_child(shell_data *data, char *path);
void exit_with_error(shell_data *data, const char *format, ...);
int is_builtin_command(const char *command);
void cd_command(shell_data *data);
char *_strncpy(char *dest, const char *src, size_t n);
size_t _strlen(const char *s);
char *_strchr(const char *s, int c);
int _strcmp(const char *s1, const char *s2);
void handle_echo_command(shell_data *data);
char *_which(char *filename, char *path);
int find_file(char *path);
void handle_setenv(shell_data *data);
void handle_unsetenv(shell_data *data);
int _unsetenv(const char *name);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
char *_strdup(char *str);
char *_strconcat(const char *str1, const char *str2);
char *_strcpy(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
int update_environment_variable(const char *name, const char *value);
int add_environment_variable(const char *name, const char *value);
void execute_builtin_command(shell_data *data);
void execute_external_command(shell_data *data);

#endif /* SHELL_H */
