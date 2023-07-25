#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
* get_path - Get the full path of command
* @data: pointer to shell_data struct
* @command: command line argument
* Return: path of command
*/

char *get_path(shell_data *data, const char *command  __attribute__((unused)))
{
	char *fullpath;
	char *path = _getenv("PATH");
	char *path_error = "not found";
	
	fullpath = data->args[0];
	if (access(fullpath, X_OK) == -1)
	{
		fullpath = _which(data->args[0], path);
		if (path == NULL || path[0] == '\0')
		{
			if (path[0] == '\0')
				return data->args[0];
			return NULL;
		}
		if (fullpath == NULL)
			return path_error;

	}
	return (fullpath);
}


int find_file(char *path)
{
        struct stat buff;
        return ((stat(path, &buff) == 0));
}
  
char *_which(char *filename, char *path)
{
        char *path_cpy;
        char *tokens[1024];
        char *pathname;
        int i;
	  if (path == NULL)
        {
          return (NULL);
        }
        path_cpy = _strdup(path);

        /* Tokenize path */
        i = 0;
        tokens[i] = strtok(path_cpy, ":");

        while (tokens[i] != NULL)
        {
                pathname = malloc(_strlen(tokens[i]) + _strlen(filename) + 2);
                sprintf(pathname, "%s/%s", tokens[i], filename);

                if (find_file(pathname))
                {
                        free(path_cpy);
                        return(pathname);
                }

                free(pathname);
                i++;
                tokens[i] = strtok(NULL, ":");
        }

        free(path_cpy);
        return (NULL);
}

