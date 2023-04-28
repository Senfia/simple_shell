#include "headers.h"

/**
 * asignLine - assigns the line var for _getLine
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void asignLine(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFFSIZE)
			*n = j;

		else
			*n = BUFFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFFSIZE)
			*n = j;
		else
			*n = BUFFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_StirCpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * _getLine - Read inpt from stream
 * @lineptr: buffer that stores the input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t _getLine(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFFSIZE)
			buffer = _reallcmem(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	asignLine(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
