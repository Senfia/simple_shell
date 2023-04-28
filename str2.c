#include "headers.h"

/**
 * _striDup - duplicates a str in the heap memory.
 * @s: char pointer str
 * Return: duplicated str
 */
char *_striDup(const char *s)
{
	char *new;
	size_t len;

	len = _striLength(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memCopy(new, s, len + 1);
	return (new);
}

/**
 * _striLength - the length of a string.
 * @s: char pointer
 * Return: Always 0.
 */
int _striLength(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * comChar - compares chars of strings
 * @str: string input.
 * @delim: delimiter.
 * Return: 1 if equals,else 0 .
 */
int comChar(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: string input.
 * @delim: delimiter.
 * Return: string splited.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (comChar(str, delim))
			return (NULL);
		splitted = str;
		i = _striLength(str);
		str_end = &str[i];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{

		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;

		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}

/**
 * _get_numb - defines string passed is a number
 * @s: string input
 * Return: 1 if string is a number. 0 in other case.
 */
int _get_numb(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
