#include "shell.h"
#include <stddef.h>

/**
 * _strpbrk - Locates the first occurrence of any character from the 'accept'
 *            string in the 'str' string.
 * @str: The string to be searched.
 * @accept: The string containing the characters to match.
 *
 * Return: A pointer to the first occurrence in 'str' of any character from
 *         'accept', or NULL if no match is found.
 */
char *_strpbrk(const char *str, const char *accept)
{
	const char *s1 = str;
	const char *s2;

	while (*s1)
	{
		s2 = accept;
		while (*s2)
		{
			if (*s1 == *s2)
				return ((char *)s1);
			s2++;
		}
		s1++;
	}

	return (NULL);
}

/**
 * tokenize - tokenize a string into an array of strings
 * @data: shell data struct
 * Return: void
 */


void tokenize(shell_data *data)
{
	const char *delim = " \t\n";
	char *line = data->line;
	int num_args = 0;
	int total_args = 0;


	while (*line && num_args < MAX_ARGS - 1)
	{
		while (*line && _strchr(delim, *line))
			line++;

		if (*line == '\0' || *line == '#')
			break;
		data->args[total_args++] = line;
		num_args++;

		while (*line && !_strchr(delim, *line))
			line++;

		if (*line)
			*line++ = '\0';
	}

	data->args[num_args] = NULL;
	data->num_args = num_args;
}
