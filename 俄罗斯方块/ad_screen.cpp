#include "header.h"

int ad_screen(int x, int y)//此坐标为广告中心坐标
{
	ad_scr(x, y);
	resurrection_coin += 5;
	return 0;
}