#include "headers.h"

/**
 * _get_signal - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void _get_signal(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
