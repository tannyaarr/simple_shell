#include "shell.h"

/**
 * init_shell_data - SHell data initialization
 * @data: Struct to store data
 * Return: void
 */

void init_shell_data(shell_data *data)
{
	data->paths[0] = "/bin";
	data->paths[1] = "/usr/bin";
	data->paths[2] = NULL;

	data->line = NULL;
	data->num_args = 0;
}



/**
 * free_shell_data - Free memory of shell data
 * @data: Struct to store data
 * Return: void
 */

void free_shell_data(shell_data *data)
{
	if (data->line != NULL)
	{
		free(data->line);
		data->line = NULL;
	}
}

/**
 * print_env - Print environment
 * Return: void
 */

void print_env(void)
{
	char **env = environ;
	char newline = '\n';

	while (*env != NULL)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, &newline, 1);
		env++;
	}
}
