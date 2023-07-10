#include "header.h"

bool end_screen(int x,int y)
{
    general1_scr(x,y,2);//调用打印程序

    Sleep(100);
    
    return general_operate_identify(x,y,2);//识别操作并返回
}