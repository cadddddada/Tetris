#include "header.h"

int mode_screen()
{
	mode_scr(400, 244);

	return mode_operate_identify(400, 244);
}