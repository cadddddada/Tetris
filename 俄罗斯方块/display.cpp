#include "header.h"
//��ť���
void button(int x, int y, int w, int h, const char* ch)
{
    setbkmode(TRANSPARENT);//�������屳��͸��
    roundrect(x, y, x + w, y + h, h / 2, h / 2);
    char text_[50] = { 0 };//��ť������
    strcpy_s(text_, ch);//����
    settextstyle(20, 0, "����");
    int tx = x + (w - textwidth(text_)) / 2;
    int ty = y + (h - textheight(text_)) / 2;
    outtextxy(tx, ty, text_);
}

//��Ԫ�����
void cell(int x, int y, int w, int h, const int name, const int score)
{
    setbkmode(TRANSPARENT);//�������屳��͸��
    rectangle(x, y, x + w, y + h);
    char ch[20];
    settextstyle(20, 0, "����");
    int ty = y + (h - textheight(ch)) / 2;
    _itoa_s(name, ch, 10);
    outtextxy(x + 20, ty, ch);
    outtextxy(x + 70, ty, "�÷֣�");
    _itoa_s(score, ch, 10);
    outtextxy(x + 125, ty, ch);
}

//ѡ������ӡ����
void arch_scr(int x, int y)
{
    cleardevice();
    rectangle(x, y, x + 500, y + 312);
    settextstyle(60, 0, _T("�������ڼ���"));
    char text_[50] = { "�浵" };
    outtextxy(x + (500 - textwidth(text_)) / 2, y + 40, _T(text_));
    for(int i = score_elem_len > 5 ? score_elem_len - 5 : 0, kk = 0; i <= score_elem_len; i++, kk++)
        cell(x + elem_axis[kk].first, y + elem_axis[kk].second, 150, 40, score_elem[i % 6][0], score_elem[i % 6][1]);
    if(score_elem_len != -1) button(x + 200, y + 275, 100, 28, "��մ浵");
}

//ͨ�ô�ӡ����
void general_scr(int x, int y,int style)
{
    string headline[3] = { "����˹����" ,"��ͣ" ,"����" };
    string top_prompt[3] = { "","��ǰ������00��" ,"��ǰ������00��"};
    string bottom_prompt[3] = { "��Esc���˳���Ϸ","��Esc��������Ϸ","��Esc���������˵�" };
    string fir_button[3] = { "��ʼ��Ϸ" ,"ֱ���˳�" ,"����һ��" };
    string sec_button[3] = { "��ȡ�浵" ,"���沢�˳�" ,"�˳�" };

    if((fraction % 100) / 10)
        top_prompt[1][10] = top_prompt[2][10] = (fraction % 100) / 10 + '0';
    else
        top_prompt[1][10] = top_prompt[2][10] = ' ';
    top_prompt[1][11] = top_prompt[2][11] = fraction % 10 + '0';
    cleardevice();
    rectangle(x, y, x + 500, y + 312);
    settextstyle(60, 0, _T("�������ڼ���"));
    outtextxy(x + (500 - textwidth(headline[style].c_str())) / 2, y + 40, _T(headline[style].c_str()));
    settextstyle(20, 0, _T("����"));
    outtextxy(x + (500 - textwidth(top_prompt[style].c_str())) / 2, y + 120, _T(top_prompt[style].c_str()));
    button(x + 150, y + 164, 200, 40, fir_button[style].c_str());
    button(x + 150, y + 225, 200, 40, sec_button[style].c_str());
    settextstyle(14, 0, _T("����"));
    outtextxy(x + (500 - textwidth(bottom_prompt[style].c_str())) / 2, y + 285, _T(bottom_prompt[style].c_str()));
}

//��Ϸ�������ӡ����
void draw_map(int x, int y)
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
            if(mapp[i][j])
            {
                setfillcolor(RGB(color_elem[mapp[i][j]][0],
                    color_elem[mapp[i][j]][1], color_elem[mapp[i][j]][2]));
                fillrectangle(y + j * 20, x + i * 20, y + j * 20 + 20, x + i * 20 + 20);
            }
        }
    }
}

//��Ϸ������1��ӡ����
void draw_small_windows(int x, int y, int shapenum, int style)
{
    setbkcolor(BLACK);
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID);
    settextstyle(16, 0, _T("����"));
    outtextxy(y + 12, x, _T("��һ��ͼ��"));
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
    };//ע��˴���first��second��shape�е��෴
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

//��Ϸ������2��ӡ����
void draw_fraction(int x, int y)
{
    TCHAR s[5];
    setbkcolor(BLACK);
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID);
    settextstyle(16, 0, _T("����"));
    outtextxy(y + 10, x + 10, _T("��  �ȣ�"));
    outtextxy(y + 10, x + 42, _T("��  ����"));
    outtextxy(y + 10, x + 74, _T("��߷֣�"));
    rectangle(y, x, y + 100, x + 100);
    _stprintf_s(s, _T("%d"), hard_num);
    outtextxy(y + 72, x + 10, s);
    _stprintf_s(s, _T("%d"), fraction);
    outtextxy(y + 72, x + 42, s);
    _stprintf_s(s, _T("%d"), max_score);
    outtextxy(y + 72, x + 74, s);

}

