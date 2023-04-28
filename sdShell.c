#include "headers.h"

/**
 * cd_Main - changes current directory
 * @datash: data relevant
 * Return: 1 on success
 */
int cd_Main(data_shell *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ishome = _StirCmpr("$HOME", dir);
		ishome2 = _StirCmpr("~", dir);
		isddash = _StirCmpr("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_To_Home(datash);
		return (1);
	}

	if (_StirCmpr("-", dir) == 0)
	{
		cd_prev(datash);
		return (1);
	}

	if (_StirCmpr(".", dir) == 0 || _StirCmpr("..", dir) == 0)
	{
		cd_Dot(datash);
		return (1);
	}

	cd_Tot(datash);

	return (1);
}
