#include "header.h"

bool end_screen(int x,int y)
{
    general_scr(x,y,2);//���ô�ӡ����

    Sleep(100);
    
    return general_operate_identify(x,y,2);//ʶ�����������
}