#include "shell.h"

/**
 * get_command_path -Get shell command path
 * @data: Struct to store data
 * Return: shell command
 */

char *get_command_path(shell_data *data)
{
	char *path;

	if (data->args[0][0] == '/')
	{
		return (data->args[0]);
	}
	else
	{
		path = get_path(data, data->args[0]);
		return ((path != NULL) ? path : NULL);
	}
}

/**
 * wait_for_child - Wait function for parent process
 * @pid: process ID
 * @status: return value
 * Return: void
 */

void wait_for_child(pid_t pid, int *status)
{
	while (waitpid(pid, status, WUNTRACED) == -1)
	{
		if (errno != EINTR)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
}




/**
 * _unsetenv_variable - Remove an environment variable
 * @variable: The name of the environment variable to be removed
 * Return: void
 */
int _unsetenv(const char *name)
{
	char **env = environ, **arr;
	int len, nameLength;
	int env_cnt = 0;
	int i, j;

	if (name == NULL)
		return (-1);

	while (*env != NULL)
	{
		env_cnt++;
		env++;
	}

	arr = malloc((env_cnt + 1) * sizeof(char *));
	if (arr == NULL)
		return (-1);

	env = environ;
	i = 0;
	j = 0;
	nameLength = _strlen(name);

	while (*env != NULL)
	{
		if (_strncmp(name, *env, nameLength) != 0 || (*env)[nameLength] != '=')
		{
			len = _strlen(*env);
			arr[i] = malloc((len + 1) * sizeof(char));
			if (arr[i] == NULL)
			{
				for (j = 0; j < i; j++)
				{
					free(arr[j]);
				}
				free(arr);
				return (-1);
			}
			_strcpy(arr[i], *env);
			i++;
		}
		env++;
	}
	arr[i] = NULL;
	environ = arr;
	return (0);
}


/**
 * is_builtin_command - Check if command is a built-in command
 * @command: Command name
 * Return: 1 if built-in, 0 otherwise
 */

int is_builtin_command(const char *command)
{
	return ((_strcmp(command, "setenv") == 0 ||
				_strcmp(command, "unsetenv") == 0));
}
