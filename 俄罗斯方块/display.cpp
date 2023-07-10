#include "header.h"
//按钮组件
void button(int x, int y, int w, int h, const char* ch)
{
    setbkmode(TRANSPARENT);//设置字体背景透明
    roundrect(x, y, x + w, y + h, h / 2, h / 2);
    char text_[50] = { 0 };//按钮内容物
    strcpy_s(text_, ch);//复制
    settextstyle(20, 0, "黑体");
    int tx = x + (w - textwidth(text_)) / 2;
    int ty = y + (h - textheight(text_)) / 2;
    outtextxy(tx, ty, text_);
}

//单元格组件
void cell(int x, int y, int w, int h, const int name, const int score)
{
    setbkmode(TRANSPARENT);//设置字体背景透明
    rectangle(x, y, x + w, y + h);
    char ch[20];
    settextstyle(20, 0, "黑体");
    int ty = y + (h - textheight(ch)) / 2;
    _itoa_s(name, ch, 10);
    outtextxy(x + 20, ty, ch);
    outtextxy(x + 70, ty, "得分：");
    _itoa_s(score, ch, 10);
    outtextxy(x + 125, ty, ch);
}

//选择界面打印程序
void arch_scr(int x, int y)
{
    cleardevice();
    rectangle(x, y, x + 500, y + 312);
    settextstyle(60, 0, _T("方正经黑简体"));
    char text_[50] = { "存档" };
    outtextxy(x + (500 - textwidth(text_)) / 2, y + 40, _T(text_));
    for(int i = score_elem_len > 5 ? score_elem_len - 5 : 0, kk = 0; i <= score_elem_len; i++, kk++)
        cell(x + elem_axis[kk].first, y + elem_axis[kk].second, 150, 40, score_elem[i % 6][0], score_elem[i % 6][1]);
    if(score_elem_len != -1) button(x + 200, y + 275, 100, 28, "清空存档");
}

//通用打印程序
void general_scr(int x, int y,int style)
{
    string headline[3] = { "俄罗斯方块" ,"暂停" ,"结束" };
    string top_prompt[3] = { "","当前分数：00分" ,"当前分数：00分"};
    string bottom_prompt[3] = { "按Esc键退出游戏","按Esc键返回游戏","按Esc键返回主菜单" };
    string fir_button[3] = { "开始游戏" ,"直接退出" ,"再来一局" };
    string sec_button[3] = { "读取存档" ,"保存并退出" ,"退出" };

    if((max(fraction[0], fraction[1]) % 100) / 10)
        top_prompt[1][10] = top_prompt[2][10] = (max(fraction[0],fraction[1]) % 100) / 10 + '0';
    else
        top_prompt[1][10] = top_prompt[2][10] = ' ';
    top_prompt[1][11] = top_prompt[2][11] = max(fraction[0], fraction[1]) % 10 + '0';
    cleardevice();
    rectangle(x, y, x + 500, y + 312);
    settextstyle(60, 0, _T("方正经黑简体"));
    outtextxy(x + (500 - textwidth(headline[style].c_str())) / 2, y + 40, _T(headline[style].c_str()));
    settextstyle(20, 0, _T("黑体"));
    outtextxy(x + (500 - textwidth(top_prompt[style].c_str())) / 2, y + 120, _T(top_prompt[style].c_str()));
    button(x + 150, y + 164, 200, 40, fir_button[style].c_str());
    button(x + 150, y + 225, 200, 40, sec_button[style].c_str());
    settextstyle(14, 0, _T("黑体"));
    outtextxy(x + (500 - textwidth(bottom_prompt[style].c_str())) / 2, y + 285, _T(bottom_prompt[style].c_str()));
}

//模式界面打印程序
void mode_scr(int x, int y)
{
    cleardevice();
    rectangle(x, y, x + 500, y + 312);
    settextstyle(60, 0, _T("方正经黑简体"));
    char text_[50] = { "模式" };
    outtextxy(x + (500 - textwidth(text_)) / 2, y + 40, _T(text_));
    button(x + 150, y + 124, 200, 40, "经典模式");
    button(x + 150, y + 184, 200, 40, "随机旋转模式");
    button(x + 150, y + 244, 200, 40, "双人模式");
}

//游戏主界面打印程序
void draw_map(int x, int y,int user)
{
    setbkcolor(BLACK);
    setlinecolor(WHITE);
    setlinestyle(PS_DOT);
    line(y, x + 80, y + 300, x + 80);
    setlinestyle(PS_SOLID);
    rectangle(y, x, y + 300, x + 600);
    for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            setlinestyle(PS_SOLID);
            if(mapp[user][i][j])
            {
                setfillcolor(RGB(color_elem[mapp[user][i][j]][0],
                    color_elem[mapp[user][i][j]][1], color_elem[mapp[user][i][j]][2]));
                fillrectangle(y + j * 20, x + i * 20, y + j * 20 + 20, x + i * 20 + 20);
            }
        }
    }
}

//游戏副界面1打印程序
void draw_small_windows(int x, int y, int shapenum, int style)
{
    setbkcolor(BLACK);
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID);
    settextstyle(16, 0, _T("黑体"));
    outtextxy(y + 12, x, _T("下一个图形"));
    x += 20;
    rectangle(y, x, y + 100, x + 100);
    int i, j;
    pair<int, int> orgin[7][4] =
    { {{30,30},{30,30},{30,30},{30,30}},
      {{40,10},{10,40},{40,10},{10,40}},
      {{20,30},{30,20},{20,30},{30,20}},
      {{20,30},{30,20},{20,30},{30,20}},
      {{30,20},{20,30},{30,20},{20,30}},
      {{30,20},{20,30},{30,20},{20,30}},
      {{20,30},{30,20},{20,30},{30,20}},
    };//注意此处的first、second与shape中的相反
    y += orgin[shapenum][style].first;
    x += orgin[shapenum][style].second;
    for(int p = 0; p < 4; p++)
    {
        i = shape[shapenum][style][p].first;
        j = shape[shapenum][style][p].second;

        setfillcolor(RGB(color_elem[shapenum + 1][0],
            color_elem[shapenum + 1][1], color_elem[shapenum + 1][2]));
        fillrectangle(y + j * 20, x + i * 20, y + j * 20 + 20, x + i * 20 + 20);
    }
}

//游戏副界面2打印程序
void draw_fraction(int x, int y,int user)
{
    TCHAR s[5];
    setbkcolor(BLACK);
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID);
    settextstyle(16, 0, _T("黑体"));
    outtextxy(y + 10, x + 10, _T("难  度："));
    outtextxy(y + 10, x + 42, _T("分  数："));
    outtextxy(y + 10, x + 74, _T("最高分："));
    rectangle(y, x, y + 100, x + 100);
    _stprintf_s(s, _T("%d"), hard_num);
    outtextxy(y + 72, x + 10, s);
    _stprintf_s(s, _T("%d"), fraction[user]);
    outtextxy(y + 72, x + 42, s);
    _stprintf_s(s, _T("%d"), max_score);
    outtextxy(y + 72, x + 74, s);

}

//
void Two_player_win_display(int x,int y,int fra2,int fra1)//user is win, (x,y) is first(x,y)
{
    string out_elem[3][2] = { "你赢了" ,"你输了" ,"你输了" ,"你赢了" ,"平 局","平 局" };
    int out_tip;

    if(fra1 > fra2)
        out_tip = 0;
    else if(fra1 < fra2)
        out_tip = 1;
    else
        out_tip = 2;

    settextstyle(80, 0, _T("黑体"));
    outtextxy(x + (300- textwidth(out_elem[out_tip][0].c_str()))/2, y + 260, _T(out_elem[out_tip][0].c_str()));
    outtextxy(x + (300 - textwidth(out_elem[out_tip][1].c_str())) / 2 +650, y + 260, _T(out_elem[out_tip][1].c_str()));
    settextstyle(20, 0, _T("黑体"));
    char text_[] = "按下Esc键继续";
    outtextxy(x + 85, y + 350, _T(text_));
    outtextxy(x + 85 + 650, y + 350, _T(text_));

    flushmessage(EM_KEY);
    while(1)
    {
        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)//ESC键
        {
            return;
        }
    }
}
