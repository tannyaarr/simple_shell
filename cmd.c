#include "shell.h"

/**
 * handle_echo_command - handles echo command
 * @data: a pointer to the data to be processed
 * Return: the results of the processing
 */

void handle_echo_command(shell_data *data)
{
	int i;

	for (i = 1; i < data->num_args; i++)
	{
		printf("%s", data->args[i]);

		if (i != data->num_args - 1)
		{
			printf(" ");
		}
	}
	printf("\n");

	if (data->line != NULL)
	{
		free(data->line);
		data->line = NULL;
	}

}

/**
 * _getenv - gets environment
 * @name: name of environment to be printed
 * Return: Environment variable value
 */

char *_getenv(const char *name)
{
	int nameLen = _strlen(name);
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(name, environ[i], nameLen) == 0 && environ[i][nameLen] == '=')
		{
			return (environ[i] + nameLen + 1);
		}
	}

	return (NULL);
}
