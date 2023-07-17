#include"header.h"

int x[2], y[2];
int dog_tip[2];//下落计时器
int press_tip[2];//加速按键标记
int key_tip = 0;//方向键计时器（不可重复初始化）
int hard_tip[2] = { 1,1 };//难度计时器（不可重复初始化）
int shapenum[2];//图形序号 0~6
int style[2];//图形状态 0~3
int sh2[2], st2[2];//下一个图形信息
int stmp_common;//通用临时变量
double ex_time_key[2];
double ex_time_down[2];
double ex_time_swap;

default_random_engine et;
uniform_int_distribution<int> sh(0, 6);
uniform_int_distribution<int> st(0, 3);
uniform_int_distribution<int> sk(0, 1000);


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
	LARGE_INTEGER Freq;//高精度时钟
	LARGE_INTEGER CurrentTime;
	LARGE_INTEGER LastTime_key[2];
	LARGE_INTEGER LastTime_down[2];
	LARGE_INTEGER LastTime_swap;
	QueryPerformanceCounter(&LastTime_key[0]);//获取开始时间数
	QueryPerformanceCounter(&LastTime_key[1]);//获取开始时间数
	QueryPerformanceCounter(&LastTime_down[0]);//获取开始时间数
	QueryPerformanceCounter(&LastTime_down[1]);//获取开始时间数
	QueryPerformanceCounter(&LastTime_swap);//获取开始时间数
	QueryPerformanceFrequency(&Freq);//时钟计时器频率
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
		
		QueryPerformanceCounter(&CurrentTime);
		ex_time_key[0] = (double)(CurrentTime.QuadPart - LastTime_key[0].QuadPart) * 1000 / (double)Freq.QuadPart;
		if(ex_time_key[0] >= (165.0 - hard_num * 12.5))
		{
			LastTime_key[0] = CurrentTime;
			if(Key_presses_tip[0])
				Key_presses_tip[0] = 0;
		}
		stmp_common = Key_presses_use1(x, y, shapenum, style, press_tip);
		if(stmp_common==1) //键盘读入
		{
			if(stop_screen(400, 244))//按下ESC键，并return true，退出游戏界面
				return 0;
		}
		else if(stmp_common==0)//松开按键，重置key计时器
			LastTime_key[0].QuadPart = CurrentTime.QuadPart + Freq.QuadPart/hard_num/2;

		if(mode == 3)
		{
			ex_time_key[1] = (double)(CurrentTime.QuadPart - LastTime_key[1].QuadPart) * 1000 / (double)Freq.QuadPart;
			if(ex_time_key[1] >= (165.0 - hard_num * 12.5))
			{
				LastTime_key[1] = CurrentTime;
				if(Key_presses_tip[1])
					Key_presses_tip[1] = 0;
			}
			stmp_common = Key_presses_use2(x, y, shapenum, style, press_tip);
			if(stmp_common == 0)//松开按键，重置key计时器
				LastTime_key[1].QuadPart = CurrentTime.QuadPart + Freq.QuadPart / hard_num / 2;
		}

		for(int con = 0; con < control; con++)
		{
			QueryPerformanceCounter(&CurrentTime);
			if(mode == 2)//模式2 随机旋转
			{
				ex_time_swap = (double)(CurrentTime.QuadPart - LastTime_swap.QuadPart) * 1000 / (double)Freq.QuadPart;
				if(ex_time_swap >= 1000 + sk(et) * 10)
				{
					//printf("%d\n", (int)((double)(CurrentTime.QuadPart) / (double)Freq.QuadPart * 1000));//帧率监测
					LastTime_swap = CurrentTime;
					if(check(x[con], y[con], shapenum[con], (style[con] + 1) % 4, con))
						style[con]++;
					style[con] %= 4;
				}
			}
			ex_time_down[con] = (double)(CurrentTime.QuadPart - LastTime_down[con].QuadPart) * 1000 / (double)Freq.QuadPart;
			if(ex_time_down[con] >= (330.0 - hard_num * 25.0) || (press_tip[con] && ex_time_down[con] >= (33.0 - hard_num * 2.5)))//判定下落
			{
				LastTime_down[con] = CurrentTime;

				//printf("%d\n", (int)((double)(CurrentTime.QuadPart) / (double)Freq.QuadPart * 1000));//帧率监测
				if(!time_dog(x[con], y[con], shapenum[con], style[con], con))//下落失败，图形触底
				{
					dispose_shape(x[con], y[con], shapenum[con], style[con], 1, con);
					fraction[con] += line_check(con);//清除线判定
					hard_tip[con]++;
					if(end_check(con))//游戏结束
					{
						if(mode == 3)
							Two_player_win_display(100, 100, con);
						int tmp_res;
						do
						{
							flushmessage(EM_MOUSE);
							int stmp = end_screen(400, 244, mode);
							if(stmp == 2)//选择复活
								tmp_res = resurrection(400, 244);
							else
							{
								resurrection_coin += max(fraction[0], fraction[1]);//根据游戏分数获取复活币
								store_score();//存储
								return stmp;
							}
						} while(!tmp_res);
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
			draw_fraction(450 + 325, 300, 0);
		}
		else
			for(int con = 0; con < control; con++)
			{
				draw_map(100, 750 - 650 * con, con);
				draw_small_windows(100, 1100 - 650 * con, sh2[con], st2[con]);
				draw_fraction(1100 - 650 * con, 300, con);
			}

		EndBatchDraw();
		//绘图区域结束

	}
	return 0;
}
