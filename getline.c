#include "shell.h"

/**
 * append_to_line - appends input to the line
 * @data: shell data
 * @input: input buffer
 * @size: size of the input buffer
 * @total_chars_read: total characters read so far
 * Return: 0 on success, -1 on failure
 */

int append_to_line(shell_data *data, char *input,
		ssize_t size, ssize_t *total_chars_read)
{
	data->line = realloc(data->line, *total_chars_read + size + 1);
	if (data->line == NULL)
		return (-1);
	memcpy(data->line + *total_chars_read, input, size);
	*total_chars_read += size;
	return (0);
}

/**
 * _getline - gets line from stream
 * @data: shell data
 * Return: number of characters read
 */

ssize_t _getline(shell_data *data)
{
    char input[READ_BUF_SIZE];
    ssize_t chars_read = 0, i, total_chars_read = 0;

    while (1)
    {
        chars_read = read(STDIN_FILENO, input, READ_BUF_SIZE);
        if (chars_read == -1)
        {
            if (errno == EINTR)
                continue;
            else
                return (-1);
        }
        else if (chars_read == 0)
            break;

        for (i = 0; i < chars_read; i++)
        {
            if (input[i] == '\n')
            {
                if (append_to_line(data, input, i, &total_chars_read) == -1)
                    return (-1);

                tokenize(data); 
                return (total_chars_read);
            }
        }

        if (append_to_line(data, input, chars_read, &total_chars_read) == -1)
            return (-1);
    }

    if (total_chars_read > 0)
    {
        data->line = realloc(data->line, total_chars_read + 1);
        if (data->line == NULL)
            return (-1);
        data->line[total_chars_read] = '\0';
    }

    return (total_chars_read);
}
