#include "shell.h"


/**
 * run_shell_command - Execute the shell command
 * @data: Pointer to the shell data structure
 * Return: void
 */

void run_shell_command(shell_data *data)
{
	pid_t pid;
	int exit_status;
	int child_exit_status;

	if (data->args[0] == NULL)
	{
		return;
	}
	if (_strcmp(data->args[0], "exit") == 0)
		exit(0);
	else if (_strcmp(data->args[0], "env") == 0)
		print_env();
	else if (_strcmp(data->args[0], "setenv") == 0)
	{
		handle_setenv(data);
	}
	else if (_strcmp(data->args[0], "unsetenv") == 0)
	{
		handle_unsetenv(data);
	}
	else if (_strcmp(data->args[0], "cd") == 0)
		cd_command(data);
	else if (_strcmp(data->args[0], "echo") == 0)
		handle_echo_command(data);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			exit_with_error(data, "Fork error");
		}

		else if (pid == 0)
		{
			exit_status = execute_command_child(data, get_command_path(data));
			exit(exit_status);
		}
		else
		{
			waitpid(pid, &exit_status, 0);
			if (WIFEXITED(exit_status))
			{
				child_exit_status = WEXITSTATUS(exit_status);
				if (child_exit_status != 0)
				{
					errno = child_exit_status;
				}
			}
			else
			{
				errno = 127;
			}
		}
	}
}

/**
 * main - Entry point of the shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * Return: 0 on success, otherwise an error code.
 */

int main(int argc, char **argv)
{
	int interactive_mode;
	shell_data data;

	init_shell_data(&data);

	if (argc > 1)
	{
		data.program_name = argv[0];
		run_file_command(argv[0], argv[1], &data);
	}
	else
	{
		data.program_name = argv[0];
		interactive_mode = isatty(STDIN_FILENO);
		if (interactive_mode)
		{
			while (1)
			{
				printf("($) ");
				fflush(stdout);

				if (read_shell_input(&data) == -1)
				{
					free_shell_data(&data);
					exit(EXIT_FAILURE);
				}

				if (data.line == NULL)
				{
					break;
				}

				run_shell_command(&data);
			}
		}
		else
		{
			while (read_shell_input(&data) == 0)
			{
				run_shell_command(&data);
			}
			if (errno > 100)
				exit(errno);
		}
	}

	free_shell_data(&data);
	return (0);
}

/**
 * run_file_command - File command function
 * @program_name: name of program
 * @file_name: name of file
 * @data: shell data
 */

void run_file_command(const char *program_name, const char *file_name,
		shell_data *data)
{
	FILE *file;
	char line[READ_BUF_SIZE];

	file = fopen(file_name, "r");
	if (file == NULL)
	{
		perror(program_name);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
		line[strcspn(line, "\n")] = '\0';
		data->line = strdup(line);
		tokenize(data);
		run_shell_command(data);
		free(data->line);
		data->line = NULL;
	}

	fclose(file);
}

/**
 * read_shell_input - reads shell input
 * @data: Struct to store data
 * Return: 0 if successful, -1 on error or end of input
 */

int read_shell_input(shell_data *data)
{
	ssize_t chars_read;
	size_t input_size = READ_BUF_SIZE;

	if (data->line != NULL)
	{
		free(data->line);
		data->line = NULL;
	}

	data->line = malloc(input_size);

	if (data->line == NULL)

	{
		perror("malloc");
		free_shell_data(data);
		return (-1);
	}

	chars_read = /*_getline(data)*/getline(&(data->line), &input_size, stdin);
	if (chars_read == -1)
	{
		free_shell_data(data);
		return (-1);
	}

	if (chars_read == 0 || chars_read == EOF)
		return (-1);

	if (data->line[chars_read - 1] == '\n')
		data->line[chars_read - 1] = '\0';

	daiiita->line_num++;
	tokenize(data);
	return (0);
}
