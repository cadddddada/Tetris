#include "header.h"

int error_screen(int x, int y)
{
	error_scr(x, y);

	if(error_operate_identify(x, y))
	{
		ad_screen(1300 / 2, 800 / 2);
		return 1;
	}
	else
		return 0;
}