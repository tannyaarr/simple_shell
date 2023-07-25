#include "shell.h"

/**
 * cd_command - Change the current directory of the process
 * @data: Pointer to the shell data structure
 * Return: void
 */
void cd_command(shell_data *data)
{
	char *diry;
	char curr_dir[PATH_MAX];

	if (data->num_args == 1 || _strcmp(data->args[1], "~") == 0)
		diry = getenv("HOME");
	else if (_strcmp(data->args[1], "-") == 0)
		diry = _getenv("OLDPWD");
	else
		diry = data->args[1];

	if (diry == NULL)
	{
		fprintf(stderr, "cd: Directory not found\n");
		return;
	}

	if (chdir(diry) != 0)
	{
		perror("cd");
		return;
	}

	if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
	{
		if (_setenv("PWD", curr_dir, 1) != 0)
		{
			perror("setenv");
			return;
		}
	}
	else
	{
		perror("getcwd");
		return;
	}
}
