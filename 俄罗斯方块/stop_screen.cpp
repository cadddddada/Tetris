#include "header.h"

bool stop_screen(int x,int y)
{
    general1_scr(x, y, 1);//调用打印程序

    Sleep(500);
    
    return general_operate_identify(x,y,1);//识别操作并返回
}