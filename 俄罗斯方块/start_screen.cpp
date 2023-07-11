#include"header.h"

int start_screen(int x, int y)
{
    read_score_txt();

    general1_scr(x, y, 0);//调用打印程序
    int retu;
    do
    {
        retu = general1_operate_identify(x, y, 0);//识别操作并返回
        if(retu == 3)
            instructions(950, 100);
    } while(retu == 3);
        return retu;
}
