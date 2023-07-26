#include "shell.h"

/**
 * add_environment_variable - add the environment variable
 * @name: the name to be processed
 * @value: the value to be printed
 * Return: the result
 */

int add_environment_variable(const char *name, const char *value)
{
	int nLen = _strlen(name);
	int vaLen = _strlen(value);
	char *newStr = (char *)malloc((nLen + vaLen + 2) * sizeof(char));
	int envCnt = 0;

	if (newStr == NULL)
	{
		return (-1);
	}
	sprintf(newStr, "%s=%s", name, value);

	while (environ[envCnt] != NULL)
	{
		envCnt++;
	}
	environ[envCnt] = newStr;
	environ[envCnt + 1] = NULL;
	return (0);
}

/**
 * update_environment_variable - updates the environment variable
 * @name: name of variable to be updated
 * @value: value of updated variable
 * Return: int signifying success
 **/

int update_environment_variable(const char *name, const char *value)
{
	int nLen = _strlen(name);
	int vaLen = _strlen(value);
	char **env = environ;
	char *newStr = NULL;
	char *envCpy, *myname;

	while (*env != NULL)
	{
		envCpy = _strdup(*env);
		myname = strtok(envCpy, "=");
		if (_strcmp(myname, name) == 0)
		{
			newStr = (char *)malloc((nLen + vaLen + 2) * sizeof(char));
			if (newStr == NULL)
			{
				free(envCpy);
				return (-1);
			}
			sprintf(newStr, "%s=%s", name, value);
			*env = newStr;
			free(envCpy);
			return (0);
		}
		env++;
		free(envCpy);
	}
	return (-1);
}

/**
 * _setenv - sets the environment
 * @name: name of variable to be set
 * @value: value of variable to be set
 * @overwrite: Int signifying whether to overwrite input or not
 * Return: Int signifying success or failure
 **/

int _setenv(const char *name, const char *value, int overwrite)
{
	if (_getenv(name) != NULL)
	{
		if (overwrite != 0)
		{
			return (update_environment_variable(name, value));
		}
	} else
	{
		return (add_environment_variable(name, value));
	}
	return (0);
}
