#include "header.h"

//ͨ�ò�������style�����Ĳ�ͬ����ֵ
int return_elem[3][3] = { {1,2,0},{1,1,0},{1,0,0} };

int general_operate_identify(int x,int y,int style)
{
    flushmessage(EM_KEY);
    ExMessage msg;
    while(1)
    {
        if(peekmessage(&msg, EM_MOUSE | EM_KEY))//�������Ϣ�����棬û�з��ؼ�
        {
            switch(msg.message)
            {
            case WM_LBUTTONDOWN:
                if(msg.x >= x + 150 && msg.x <= x + 150 + 200 && msg.y >= y + 164 && msg.y <= y + 164 + 40)
                {
                    return return_elem[style][0];
                }
                else if(msg.x >= x + 150 && msg.x <= x + 150 + 200 && msg.y >= y + 238 && msg.y <= y + 238 + 40)
                {
                    if(style==1)
                        archiving();
                    return return_elem[style][1];
                }
                break;
            case WM_RBUTTONDOWN:
                //�Ҽ����ݲ����ù���
                break;
            case WM_KEYDOWN:
                if(GetAsyncKeyState(VK_ESCAPE))//����ESC��
                    return return_elem[style][2];
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
        if(peekmessage(&msg, EM_MOUSE | EM_KEY))//�������Ϣ�����棬û�з��ؼ�
        {
            switch(msg.message)
            {
            case WM_LBUTTONDOWN:
                for(int i = 0; i < 6; i++)
                {
                    if(msg.x >= x + elem_axis[i].first && msg.x <= x + elem_axis[i].first + 150 && msg.y >= y + elem_axis[i].second && msg.y <= y + elem_axis[i].second + 40)
                    {
                        return score_elem[score_elem_len > 6 ? (score_elem_len + 1 + i) % 6 : i][0];
                    }
                    if(score_elem_len != -1 && msg.x >= x + 200 && msg.x <= x + 200 + 100 && msg.y >= y + 275 && msg.y <= y + 275 + 28)
                    {
                        string ch = "archive/0.txt";
                        for(int i = 1; i <= score_elem[score_elem_len][0]; i++)
                        {
                            ch[8] = i + '0';
                            remove(ch.c_str());
                        }
                        remove("archive/list.txt");
                        remove("archive/score.txt");
                        archive_processing(x, y);
                        break;
                    }
                }
                break;
            case WM_RBUTTONDOWN:
                //�Ҽ����ݲ����ù���
                break;
            case WM_KEYDOWN:
                if(GetAsyncKeyState(VK_ESCAPE))//msg.vkcode == VK_ESCAPE
                    return 0;	// �� ESC ���ص���Ϸ����
            default:
                break;
            }
        }
    }
}

int Key_presses(int& x, int& y, int shapenum, int& style, int& tip)
{
    int stx = x, sty = y, sts = style;
    flushmessage(EM_KEY);

    if(GetAsyncKeyState(VK_UP))//�ϼ�
    {
        sts++;
        sts = sts % 4;
    }
    if(GetAsyncKeyState(VK_DOWN) & 0x8000)//�¼�
    {
        tip = 1;
    }
    if(GetAsyncKeyState(VK_LEFT))//���
    {
        sty -= 1;
    }
    if(GetAsyncKeyState(VK_RIGHT))//�Ҽ�
    {
        sty += 1;
    }
    if(check(stx, sty, shapenum, sts))
        x = stx, y = sty, style = sts;
    if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)//ESC��
    {
        return 1;//����Ϸ���������ͣ���棬������ͣ�����return��һ����������
    }
    return 0;
}
