#include "header.h"
#define mplus_hzk_12 mplus_hzk_12
//按钮组件
void button(int x, int y, int w, int h, const char* ch)
{
    if(!ch[0])
        return;
    setbkmode(TRANSPARENT);//设置字体背景透明
    roundrect(x, y, x + w, y + h, h / 2, h / 2);
    char text_[50] = { 0 };//按钮内容物
    strcpy_s(text_, ch);//复制
    settextstyle(20, 0, "mplus_hzk_12");
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
    settextstyle(20, 0, "mplus_hzk_12");
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
    settextstyle(60, 0, _T("mplus_hzk_12"));
    char text_[50] = { "存档" };
    outtextxy(x + (500 - textwidth(text_)) / 2, y + 40, _T(text_));
    for(int i = score_elem_len > 5 ? score_elem_len - 5 : 0, kk = 0; i <= score_elem_len; i++, kk++)
        cell(x + elem_axis[kk].first, y + elem_axis[kk].second, 150, 40, score_elem[i % 6][0], score_elem[i % 6][1]);
    if(score_elem_len != -1) button(x + 200, y + 275, 100, 28, "清空存档");
}

//通用打印程序1
void general1_scr(int x, int y,int style)
{
    string headline[3] = { "俄罗斯方块" ,"暂停" ,"结束" };
    string top_prompt[3] = { "点击查看游戏说明","当前分数：00分" ,"当前分数：00分"};
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
    settextstyle(60, 0, _T("mplus_hzk_12"));
    outtextxy(x + (500 - textwidth(headline[style].c_str())) / 2, y + 40, (headline[style].c_str()));
    settextstyle(20, 0, _T("mplus_hzk_12"));
    outtextxy(x + (500 - textwidth(top_prompt[style].c_str())) / 2, y + 120, (top_prompt[style].c_str()));
    button(x + 150, y + 164, 200, 40, fir_button[style].c_str());
    button(x + 150, y + 225, 200, 40, sec_button[style].c_str());
    settextstyle(14, 0, _T("mplus_hzk_12"));
    outtextxy(x + (500 - textwidth(bottom_prompt[style].c_str())) / 2, y + 285, (bottom_prompt[style].c_str()));
    
    if(style == 0)
    {
        string ch = "复活币：", tmp;
        tmp=to_string(resurrection_coin);
        ch += tmp;
        settextstyle(20, 0, _T("mplus_hzk_12"));

        outtextxy(x + 380, y + 120, _T(ch.c_str()));
    }
}

//通用打印程序2
void general2_scr(int x, int y,int style)
{
    string headline[3] = { "模式" ,"结束" ,"结束" };
    string fir_button[3] = { "经典模式" ,"再来一局","再来一局" };
    string sec_button[3] = { "随机旋转模式" ,"退出","退出" };
    string tri_button[3] = { "双人模式" ,"消耗5复活币 复活",""};

    cleardevice();
    rectangle(x, y, x + 500, y + 312);
    settextstyle(60, 0, _T("mplus_hzk_12"));
    outtextxy(x + (500 - textwidth(headline[style].c_str())) / 2, y + 40, _T(headline[style].c_str()));
    button(x + 150, y + 124, 200, 40, fir_button[style].c_str());
    button(x + 150, y + 184, 200, 40, sec_button[style].c_str());
    button(x + 150, y + 244, 200, 40, tri_button[style].c_str());

    if(style==1)
    {
        string ch = "复活币：", tmp;
        tmp = to_string(resurrection_coin);
        ch += tmp;
        settextstyle(20, 0, _T("mplus_hzk_12"));

        outtextxy(x + 380, y + 90, _T(ch.c_str()));
    }
}

//文本输出程序
void text_print(int x, int y, int w, int h,int size)
{
    w -= w % (size / 2);
    string stmp[50];
     stmp[0] = "界面操作：";
     stmp[1] = "在主界面，你可以选择开始新游戏";
     stmp[2] = "或者读取历史存档";
     stmp[3] = "存档界面中，点击清空存档会清空";
     stmp[4] = "所有存档、历史最高分以及初始化";
     stmp[5] = "复活币";
     stmp[6] = "在任何界面，点击Esc均可以回退";
     stmp[8] = "游戏参数：";
     stmp[9] = "复活币：初始复活币数量为20，每";
    stmp[10] = "次复活消耗5复活币，每局游戏结";
    stmp[11] = "束时可以按分数获得复活币";
    stmp[13] = "最高分：记录历史游戏中的最高分，";
    stmp[14] = "清空存档时最高分会清零";
    stmp[16] = "游戏模式：";
    stmp[17] = "经典模式，通过方向键控制图形左";
    stmp[18] = "右移动、下落与旋转";
    stmp[20] = "随机旋转模式，图形旋转由系统随";
    stmp[21] = "机控制，不可自行控制";
    stmp[23] = "双人模式，通过ASDW控制左界面，";
    stmp[24] = "方向键控制右界面，当任意一方结";
    stmp[25] = "束游戏时，整局游戏结束，系统根";
    stmp[26] = "据双方越界情况判定，该模式不能";
    stmp[27] = "获得复活币";
    int yth = y;
    settextstyle(size, 0, _T("mplus_hzk_12"));
    for(int tip=0;tip<50;tip++)
        outtextxy(x, yth, _T(stmp[tip].c_str())),yth+=(int)size*1.2;
}

//说明界面打印程序
void instructions(int x, int y)
{
    rectangle(x, y, x + 300, y + 600);
    text_print(x + 12, y + 10, 280, 580, 17);
}
//复活失败界面
void error_scr(int x, int y)
{
    cleardevice();
    rectangle(x, y, x + 500, y + 312);
    settextstyle(60, 0, _T("mplus_hzk_12"));
    string head = "复活失败";
    outtextxy(x + (500 - textwidth(head.c_str())) / 2, y + 50, _T(head.c_str()));
    string ch = "复活币：";
    settextstyle(30, 0, _T("mplus_hzk_12"));
    ch.push_back(resurrection_coin + '0');
    outtextxy(x + (500 - textwidth(ch.c_str())) / 2, y + 134, _T(ch.c_str()));
    button(x + 150, y + 184, 200, 40, "观看广告复活");
    button(x + 150, y + 244, 200, 40, "返回");
}

//广告程序
void ad_scr(int x, int y)//此坐标为中心坐标
{
    ifstream ad_list;
    ad_list.open("ad/list.txt");
    if(!ad_list.is_open())
    {
        setlinecolor(TRANSPARENT);
        setfillcolor(BLACK);
        fillrectangle(x - 260, y - 160, x + 260, y + 160);
        char text_[] = "广告信息丢失！";
        settextstyle(40, 0, "mplus_hzk_12");
        int tx = x - textwidth(text_) / 2;
        int ty = y - textheight(text_) / 2;
        outtextxy(tx, ty, text_);
        Sleep(2500);
        return;
    }
    vector<string> elem;
    string stmp;
    while(ad_list >> stmp)
        elem.push_back(stmp);
    stmp = *elem.begin();

    // 设置图片尺寸
    int w = 201;
    int h = 195;

    int x0 = x - w / 2, y0 = y - h / 2;//左上角原点坐标
    setlinecolor(TRANSPARENT);
    setfillcolor(BLACK);
    fillrectangle(x - 260, y0 - 160, x+260, y+160);
    setlinecolor(WHITE);
    rectangle(x0 - 5, y0 - 5, x0 + w + 5, y0 + h + 5);
    int tmp = 0,time=0;
    IMAGE ad_image;
    string time_out = "广告 0";
    setlinecolor(TRANSPARENT);
    while(time<5000)
    {
        loadimage(&ad_image, elem[tmp% elem.size()].c_str(), w, h);
        tmp++,time+=120;
        putimage(x0, y0, &ad_image);
        setfillcolor(BROWN);
        fillrectangle(x0, y0, x0+34, y0+14);
        time_out[time_out.size() - 1] = (5000 - time) / 1000 + 1 + '0';
        settextstyle(10, 0, "mplus_hzk_12");
        outtextxy(x0 + 2, y0 + 2, _T(time_out.c_str()));
        Sleep(120);
    }
    setlinecolor(WHITE);
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
    settextstyle(16, 0, _T("mplus_hzk_12"));
    string prompt = "按 Esc键 或 空格键 暂停游戏";
    outtextxy(y + (300 - textwidth(prompt.c_str())) / 2, x+610  , _T(prompt.c_str()));
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
    settextstyle(16, 0, _T("mplus_hzk_12"));
    outtextxy(y + 12, x, _T("下一个图形"));
    x += 20;
    rectangle(y, x, y + 100, x + 100);
    int i, j;
    if(shapenum == -1)
        return;
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

//副界面2配置程序
std::string itostr_with_zero(int number)
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << number;
    return oss.str();
}
//游戏副界面2打印程序
void draw_fraction(int x, int y,int user)
{
    string s;
    setbkcolor(BLACK);
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID);
    settextstyle(16, 0, _T("mplus_hzk_12"));
    outtextxy(x + 26, y - 18, _T("难  度"));
    outtextxy(x + 26, y-18+135, _T("分  数"));
    outtextxy(x + 26, y-18+270, _T("最高分"));
    rectangle(x, y, x + 100, y + 100);
    rectangle(x , y+135, x + 100, y +135+ 100);
    rectangle(x, y+270, x + 100, y +270+ 100);
    settextstyle(80, 0, _T("UniDreamLED"));
    s= itostr_with_zero(hard_num);
    outtextxy(x + (100 - textwidth(s.c_str())) / 2, y + 10, _T(s.c_str()));
    s = itostr_with_zero(fraction[user]);
    outtextxy(x + (100 - textwidth(s.c_str())) / 2, y + 10+135, _T(s.c_str()));
    s = itostr_with_zero(max_score);
    outtextxy(x + (100 - textwidth(s.c_str())) / 2, y + 10+270, _T(s.c_str()));

}

//双人模式结果判定输出程序
void Two_player_win_display(int x,int y,int user)//user is win, (x,y) is first(x,y)
{
    string out_elem[3][2] = { "你赢了" ,"你输了" ,"你输了" ,"你赢了" ,"平 局","平 局" };
    int out_tip;

    if(!user)
        out_tip = 0;
    else// if(fra1 < fra2)
        out_tip = 1;
    /*else
        out_tip = 2;*/

    settextstyle(80, 0, _T("mplus_hzk_12"));
    outtextxy(x +30, y + 260, _T(out_elem[out_tip][0].c_str()));
    outtextxy(x +30 +650, y + 260, _T(out_elem[out_tip][1].c_str()));
    settextstyle(20, 0, _T("mplus_hzk_12"));
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
