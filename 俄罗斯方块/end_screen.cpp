#include "header.h"

int end_screen(int x,int y,int mode_t)
{
    int stmp;
    if(mode_t==3)
    {
        stmp = 2;
    }
    else
    {
        stmp = 1;
    }

    general2_scr(x, y, stmp);//调用打印程序
    return general2_operate_identify(x,y,stmp);//识别操作并返回
}