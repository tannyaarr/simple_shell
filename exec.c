#include "shell.h"

/**
 * handle_setenv - Handle setenv command
 * @data: Struct to store data
 * Return: void
 */

void handle_setenv(shell_data *data)
{
	if (data->num_args != 3)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return;
	}

	if (_setenv(data->args[1], data->args[2], 1) != 0)
		perror("setenv");
}

/**
 * handle_unsetenv - Handle unsetenv command
 * @data: Struct to store data
 * Return: void
 */

void handle_unsetenv(shell_data *data)
{
	if (data->num_args != 2)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE VALUE\n");
		return;
	}
	if (_unsetenv(data->args[1]) != 0)
		perror("unsetenv");
}

/**
 * execute_command_child - Execute command in child process
 * @data: Struct to store data
 * @path: Command path
 * Return: void
 */

int execute_command_child(shell_data *data, char *path)
{
	char *command = data->args[0], line_num_str[32];
	int line_num_len = snprintf(line_num_str, sizeof(line_num_str),
			"%d", data->line_num);
	char *fullpath;

	if (_strcmp(data->args[0], "echo") == 0)
		handle_echo_command(data);

	else
	{
		fullpath = get_path(data, path);
		if (fullpath == NULL)
		{
			write(STDERR_FILENO, data->program_name, _strlen(data->program_name));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, line_num_str, line_num_len);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, data->args[0], _strlen(data->args[0]));
			write(STDERR_FILENO, ": not found\n", 12);
			return (127);
		}
		else if (_strcmp(fullpath, "not found") == 0)
		{
			write(STDERR_FILENO, data->program_name, _strlen(data->program_name));
			write(STDERR_FILENO, ": line ", 7);
			write(STDERR_FILENO, line_num_str, line_num_len);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, data->args[0], _strlen(data->args[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
			return (127);
		}
		if (data->line != NULL && data->line[0] != '\0')
		{
			execve(fullpath, data->args, environ);
			exit_with_error(data, "%s: No such file or directory\n", command);
			return (127);
		}
	}
	return (0);
}

/**
 * exit_with_error - Print error message and exit with failure
 * @format: Format string
 * ...: Variable arguments
 * @data: pointer of the data to be processed
 * Return: void
 */

void exit_with_error(shell_data *data, const char *format, ...)
{
	va_list args;
	char buffer[4096];
	int len;
	char line_num_buffer[32];
	int line_num_len;

	va_start(args, format);
	len = vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	write(STDERR_FILENO, data->program_name, _strlen(data->program_name));
	write(STDERR_FILENO, ": line ", 7);
	line_num_len = snprintf(line_num_buffer, sizeof(line_num_buffer),
			"%d", data->line_num);
	write(STDERR_FILENO, line_num_buffer, line_num_len);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, buffer, len);
	exit(127);
}
