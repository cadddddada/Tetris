#include "header.h"

bool boundary_check(int x, int y, pair<int, int> stmp)
{
    return x + stmp.first >= 0 && x + stmp.first < 30 && y + stmp.second >= 0 && y + stmp.second < 15;
}

bool check(int x, int y, int shapenum, int style,int user)
{
    pair<int, int> stmp;
    for(int i = 0; i < 4; i++)
    {
        stmp = shape[shapenum][style][i];
        if(mapp[user][x + stmp.first][y + stmp.second] || !boundary_check(x, y, stmp))
            return false;
    }
    return true;
}

void del_line(int x,int user)
{
    for(int i = x; i >= 5; i--)
    {
        for(int j = 0; j < 15; j++)
            mapp[user][i][j] = mapp[user][i - 1][j];
    }
    for(int j = 0; j < 15; j++)
        mapp[user][4][j] = 0;
}

int line_check(int user)
{
    int sum = 0;
    for(int i = 29; i >= 4; i--)
    {
        int j;
        for(j = 0; j < 15; j++)
            if(!mapp[user][i][j])
                break;
        if(j == 15)
        {
            sum++;
            del_line(i++,user);
        }
    }
    return sum;//返回清除的行数
}

bool end_check(int user)
{
    for(int j = 0; j < 15; j++)
        if(mapp[user][3][j])
            return true;
    return false;
}

void dispose_shape(int x, int y, int shapenum, int style, bool tip,int user)//tip=0 means delete shape
{
    pair<int, int> stmp;
    for(int i = 0; i < 4; i++)
    {
        stmp = shape[shapenum][style][i];
        mapp[user][x + stmp.first][y + stmp.second] = (shapenum + 1) * tip;
    }
}