#include "header.h"



int general1_operate_identify(int x,int y,int style)
{
    //通用操作根据style决定的不同返回值
    int return_elem[3][4] = { {1,2,3,0},{1,1,0,0},{1,0,0,0} };
    flushmessage(EM_KEY);
    ExMessage msg;
    while(1)
    {
        if(peekmessage(&msg, EM_MOUSE | EM_KEY))//有鼠标消息返回真，没有返回假
        {
            switch(msg.message)
            {
            case WM_LBUTTONDOWN:
                if(msg.x >= x + 150 && msg.x <= x + 150 + 200 && msg.y >= y + 164 && msg.y <= y + 164 + 40)
                {
                    if(style == 1)
                    {
                        resurrection_coin += max(fraction[0], fraction[1]);//
                        store_score();
                    }
                    return return_elem[style][0];
                }
                else if(msg.x >= x + 150 && msg.x <= x + 150 + 200 && msg.y >= y + 238 && msg.y <= y + 238 + 40)
                {
                    if(style==1)
                        archiving();
                    return return_elem[style][1];
                }
                else if(msg.x >= x + 170 && msg.x <= x + 170 + 160 && msg.y >= y + 120 && msg.y <= y + 120 + 20 && style == 0)//手动开启开始界面鼠标控制
                {
                    return return_elem[style][2];
                }
                break;
            case WM_RBUTTONDOWN:
                //右键，暂不设置功能
                break;
            case WM_KEYDOWN:
                if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)//按下ESC键
                    return return_elem[style][3];
            default:
                break;
            }
        }
    }
}

int arch_operate_identify(int x,int y)
{
    flushmessage(EM_KEY);
    ExMessage msg;
    while(1)
    {
        if(peekmessage(&msg, EM_MOUSE | EM_KEY))//有鼠标消息返回真，没有返回假
        {
            switch(msg.message)
            {
            case WM_LBUTTONDOWN:
                for(int i = 0; i <= score_elem_len; i++)
                {
                    if(msg.x >= x + elem_axis[i].first && msg.x <= x + elem_axis[i].first + 150 && msg.y >= y + elem_axis[i].second && msg.y <= y + elem_axis[i].second + 40)
                    {
                        return score_elem[score_elem_len > 6 ? (score_elem_len + 1 + i) % 6 : i][0];
                    }
                    if(score_elem_len != -1 && msg.x >= x + 200 && msg.x <= x + 200 + 100 && msg.y >= y + 275 && msg.y <= y + 275 + 28)
                    {
                        string ch = "archive/", ch2 = ".txt";
                        for(int i = 1; i <= score_elem[score_elem_len][0]; i++)
                        {
                            ch += to_string(i);
                            ch += ch2;
                            remove(ch.c_str());
                        }
                        remove("archive/list.txt");
                        remove("archive/score.txt");
                        archive_processing(x, y);
                        arch_scr(x,y);
                        break;
                    }
                }
                break;
            case WM_RBUTTONDOWN:
                //右键，暂不设置功能
                break;
            case WM_KEYDOWN:
                if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)//msg.vkcode == VK_ESCAPE
                    return 0;	
            default:
                break;
            }
        }
    }
}

int general2_operate_identify(int x, int y, int style)
{
    //通用操作根据style决定的不同返回值
    int return_elem[3][4] = { {1,2,3,0},{1,0,2,0},{1,0,2,0} };
    flushmessage(EM_KEY);
    ExMessage msg;
    while(1)
    {
        if(peekmessage(&msg, EM_MOUSE | EM_KEY))//有鼠标消息返回真，没有返回假
        {
            switch(msg.message)
            {
            case WM_LBUTTONDOWN:
                if(msg.x >= x + 150 && msg.x <= x + 150 + 200 && msg.y >= y + 124 && msg.y <= y + 124 + 40)
                {
                    return return_elem[style][0];
                }
                else if(msg.x >= x + 150 && msg.x <= x + 150 + 200 && msg.y >= y + 184 && msg.y <= y + 184 + 40)
                {
                    return return_elem[style][1];
                }
                else if(msg.x >= x + 150 && msg.x <= x + 150 + 200 && msg.y >= y + 244 && msg.y <= y + 244 + 40&&style!=2)//手动屏蔽状态2的按键3
                {
                    return return_elem[style][2];
                }
                break;
            case WM_RBUTTONDOWN:
                //右键，暂不设置功能
                break;
            case WM_KEYDOWN:
                if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)//按下ESC键
                    return return_elem[style][3];
            default:
                break;
            }
        }
    }
}
int ran_nd(int a, int b)
{
    std::default_random_engine eq;
    std::uniform_int_distribution<int> u(a, b); // 左闭右闭区间
    eq.seed(time(0));
    return u(eq);
}
int Key_presses(int x[], int y[], int shapenum[], int style[], int tip[], int time,int mode)
{
    int stx0 = x[0], sty0 = y[0], sts0 = style[0],
        stx1 = x[1], sty1 = y[1], sts1 = style[1];
    flushmessage(EM_KEY);
    if((GetAsyncKeyState(VK_UP)) && !time)//上键
    {
        if(mode != 2)
            sts0++;
        sts0 = sts0 % 4;
    }
    if((GetAsyncKeyState(VK_DOWN) & 0x8000)&&x[0])//下键
    {
        tip[0] = 1;
    }
    if(GetAsyncKeyState(VK_LEFT))//左键
    {
        sty0 -= 1;
    }
    if(GetAsyncKeyState(VK_RIGHT))//右键
    {
        sty0 += 1;
    }
    if(check(stx0, sty0, shapenum[0], sts0, 0))
        x[0] = stx0, y[0] = sty0, style[0] = sts0;

    if((GetAsyncKeyState('W') & 0x8000) && !time)//W键 !time用于减少扫描次数
    {
        sts1++;
        sts1 = sts1 % 4;
    }
    if((GetAsyncKeyState('S') & 0x8000) && x[1])//S键
    {
        tip[1] = 1;
    }
    if(GetAsyncKeyState('A') & 0x8000)//A键
    {
        sty1 -= 1;
    }
    if(GetAsyncKeyState('D') & 0x8000)//D键
    {
        sty1 += 1;
    }
    if(check(stx1, sty1, shapenum[1], sts1, 1))
        x[1] = stx1, y[1] = sty1, style[1] = sts1;

    if((GetAsyncKeyState(VK_ESCAPE) & 0x8000) && !time)//ESC键
    {
        return 1;//由游戏界面调用暂停界面，根据暂停界面的return进一步处理请求
    }
    return 0;
}
