#include <stddef.h>
#include "shell.h"

/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 if the strings are equal, negative value if s1 < s2,
 * positive value if s1 > s2
 */

int _strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL)
		return (-1);
	else if (s2 == NULL)
		return (1);

	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}


/**
 * _strchr - Locate character in string
 * @s: String to search in
 * @c: Character to locate
 * Return: Pointer to the first occurrence of the character in the string,
 * or NULL if not found
 */

char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

/**
 * _strlen - Calculate the length of a string
 * @s: String
 * Return: Length of the string
 */
size_t _strlen(const char *s)
{
	const char *p = s;

	while (*p)
	{
		p++;
	}
	return (p - s);
}

/**
 * _strncpy - Copy a string to a specified length
 * @dest: Destination buffer
 * @src: Source string
 * @n: Maximum number of characters to copy
 * Return: Pointer to the destination buff
 */

char *_strncpy(char *dest, const char *src, size_t n)
{
	char *d = dest;
	const char *s = src;
	size_t i;

	for (i = 0; i < n && *s != '\0'; i++)
	{
		*d++ = *s++;
	}
	for (; i < n; i++)
	{
		*d++ = '\0';
	}
	return (dest);
}
