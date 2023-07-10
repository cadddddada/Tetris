#include"header.h"

int start_screen(int x, int y)
{
    general1_scr(x, y, 0);//调用打印程序

    return general_operate_identify(x,y,0);//识别操作并返回
}
