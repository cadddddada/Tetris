#include "header.h"
using namespace std;



int main()
{
	initgraph(650, 800);
	int tip = 0;//程序运行标记
	while(1)
	{
		if(!tip)
			tip = start_screen(75, 244);
		switch(tip)
		{
		case 0://按下ESC退出程序
			closegraph();
			return 0;
		case 1:
			set_map(-1);
			tip = game_screen();
			break;
		case 2:
			if(set_map(archive_screen(75, 244)))
				tip = game_screen();
			else
				tip = 0;
			break;
		default:
			break;
		}
	}
	closegraph();
	return 0;
}