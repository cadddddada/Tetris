#include"header.h"

using namespace std;
#define ERROR 0
#define OK 1

int time_dog(int &x, int y, int shapenum, int style)
{
    if (check(x + 1, y, shapenum, style))
        x += 1;
    else
        return false;
    return true;
}

bool game_screen()
{
    int x, y;
    int dog_tip;//下落计时器
    int press_tip;//加速按键标记
    int key_tip=1;//方向键计时器（不可重复初始化）
    int hard_tip=1;//难度计时器（不可重复初始化）
    int shapenum;//图形序号 0~6
    int style;//图形状态 0~3
    int sh2, st2;//下一个图形信息


    default_random_engine e;
    uniform_int_distribution<int> sh(0, 6);
    uniform_int_distribution<int> st(0, 3);
    e.seed(time(0));

    while(1)
    {
        x = 0, y = 7, dog_tip = 1, press_tip = 0;//初始化
        shapenum = sh2, style = st2;
        sh2 = sh(e), st2 = st(e);//随机生成图案
        while (1)
        {
            dispose_shape(x, y, shapenum, style, 0);//清除上一步产生的图形
            if(!(++key_tip % 9))
            {
                key_tip = 1;
                if(Key_presses(x, y, shapenum, style, press_tip))//键盘读入,
                {
                    if(stop_screen(75, 244))//按下ESC键，并return true，退出游戏界面
                        return 0;
                }
            }
            if (!(++dog_tip % (33-hard_num*3)) || press_tip)//判定下落
            {
                dog_tip = 1;
                if (!time_dog(x, y, shapenum, style))//下落失败，图形触底
                {
                    dispose_shape(x, y, shapenum, style, 1);
                    fraction+=line_check();//清除线判定
                    hard_tip++;
                    if (end_check())//游戏结束
                    {
                        store_score();
                        return end_screen(75, 244);//根据结束界面return值进行return，由主程序处理请求
                    }
                    break;
                }
            }
            dispose_shape(x, y, shapenum, style, 1);//写入新产生的图形

            if(!(hard_tip % 11)&&hard_num<10)//难度增加
            {
                hard_tip = 1;
                hard_num++;
            }

            //绘图区域
            BeginBatchDraw();

            cleardevice();
            draw_map(100, 100);
            draw_small_windows(100,450,sh2,st2);
            draw_fraction(300, 450);

            EndBatchDraw();
            //绘图区域结束

            Sleep(10);//时间分度为10ms

        }
    }
    return 0;
}
