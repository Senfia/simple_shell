#include "headers.h"

/**
 * readLine - reads the input string.
 * @i_eof: return value of getline function
 * Return: string input
 */
char *readLine(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
