#include "headers.h"

/**
 * _get_signal - Handles crtl + c call in prompt
 * @sig: handles Signal
 */
void _get_signal(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
