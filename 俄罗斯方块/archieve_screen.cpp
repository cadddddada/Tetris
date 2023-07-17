#include"header.h"
using namespace std;

int score_elem_len = 0;
int score_elem[6][2] = { 0 };

void archive_processing(int x, int y)
{
    score_elem_len = 0;
    memset(score_elem, 0, sizeof score_elem);
    ifstream archive_list;
    archive_list.open("archive/list.txt");
    while(archive_list >> score_elem[score_elem_len % 6][0] >> score_elem[score_elem_len % 6][1]) score_elem_len++;
    archive_list.close();
    score_elem_len--;//score_elem_len=-1 means no file
}

int archive_screen(int x, int y)
{
    archive_processing(x, y);
    arch_scr(x, y);//调用打印程序
    return arch_operate_identify(x,y);
}