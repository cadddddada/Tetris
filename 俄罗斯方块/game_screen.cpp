#include"header.h"

int x[2], y[2];
int dog_tip[2];//下落计时器
int press_tip[2];//加速按键标记
int key_tip = 0;//方向键计时器（不可重复初始化）
int hard_tip[2] = { 1,1 };//难度计时器（不可重复初始化）
int shapenum[2];//图形序号 0~6
int style[2];//图形状态 0~3
int sh2[2], st2[2];//下一个图形信息


default_random_engine et;
uniform_int_distribution<int> sh(0, 6);
uniform_int_distribution<int> st(0, 3);


int time_dog(int& x, int y, int shapenum, int style, int user)
{
	if(check(x + 1, y, shapenum, style, user))
		x += 1;
	else
		return false;
	return true;
}

void initialization_parameters(int user)
{
	x[user] = 0, y[user] = 7, dog_tip[user] = 1, press_tip[user] = 0;//初始化
	shapenum[user] = sh2[user], style[user] = st2[user];
	sh2[user] = sh(et), st2[user] = st(et);//随机生成图案
}

bool game_screen(int mode)//mode1 经典模式 mode2 随机旋转模式 mode 3 双人模式
{
	if(!mode)
		return 0;

	int control;//控制user_2的键值是否启用
	if(mode == 3)
		control = 2;
	else
		control = 1;

	et.seed(time(0));

	for(int con = 0; con < control; con++)
		initialization_parameters(con);
	while(1)
	{
		for(int con = 0; con < control; con++)
			dispose_shape(x[con], y[con], shapenum[con], style[con], 0, con);//清除上一步产生的图形
		if(!(++key_tip % 5))
		{
			key_tip %= 10;
			if(Key_presses(x, y, shapenum, style, press_tip, key_tip,mode))//键盘读入,
			{
				if(stop_screen(400, 244))//按下ESC键，并return true，退出游戏界面
					return 0;
			}
		}
		for(int con = 0; con < control; con++)
		{
			if(!(++dog_tip[con] % (33 - hard_num * 3)) || press_tip[con] == 1)//判定下落
			{
				dog_tip[con] = 1;
				if(!time_dog(x[con], y[con], shapenum[con], style[con], con))//下落失败，图形触底
				{
					dispose_shape(x[con], y[con], shapenum[con], style[con], 1, con);
					fraction[con] += line_check(con);//清除线判定
					hard_tip[con]++;
					if(end_check(con))//游戏结束
					{
						store_score();
						if(mode == 3)
							Two_player_win_display(100, 100, fraction[0] , fraction[1]);

						return end_screen(400, 244);//根据结束界面return值进行return，由主程序处理请求
					}
					initialization_parameters(con);
				}
			}
			dispose_shape(x[con], y[con], shapenum[con], style[con], 1, con);//写入新产生的图形
		}

		if(!(max(hard_tip[0], hard_tip[1]) % 11) && hard_num < 10)//难度增加
		{
			hard_tip[0] = hard_tip[1] = 1;
			hard_num++;
		}

		//绘图区域
		BeginBatchDraw();

		cleardevice();
		if(mode != 3)
		{
			draw_map(100, 100 + 325, 0);
			draw_small_windows(100, 450 + 325, sh2[0], st2[0]);
			draw_fraction(300, 450 + 325, 0);
		}
		else
			for(int con = 0; con < control; con++)
			{
				draw_map(100, 750 - 650 * con, con);
				draw_small_windows(100, 1100 - 650 * con, sh2[con], st2[con]);
				draw_fraction(300, 1100 - 650 * con, con);
			}

		EndBatchDraw();
		//绘图区域结束

		Sleep(8);//时间分度为10ms

	}
	return 0;
}
