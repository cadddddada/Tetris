#include"header.h"
using namespace std;

int mapp[31][16];
int fraction;
int hard_num;
int max_score;

bool set_map(int style)//初始化游戏地图，style=-1 means new game, style=0 means exit, other means open file
{
	if(style)
	{
		ifstream score_list;//读取最高分
		score_list.open("archive/score.txt");
		if(!(score_list >> max_score))
			max_score = 0;
		score_list.close();

		if(style == -1)
		{
			CreateDirectory("archive", NULL);
			//system("mkdir archive"); 不使用此函数是因为创建失败时会显示报错信息

			fraction = 0;
			hard_num = 1;
			memset(mapp, 0, sizeof mapp);//初始化地图为0
			return true;
		}
		else
		{
			string ch = "archive/0.txt";//从记录中读取
			ch[8] = style + '0';
			ifstream maptxt;
			maptxt.open(ch);
			maptxt >> fraction >> hard_num;
			for(int i = 0; i < 30; i++)
				for(int j = 0; j < 15; j++)
					maptxt >> mapp[i][j];
			return true;
		}
	}
	return false;
}

void store_score()//存储最高分
{
	if(fraction > max_score)
	{
		ofstream score_list;
		score_list.open("archive/score.txt");
		score_list << fraction << endl;
	}
}

void archiving()//保存游戏记录
{
	int stmp=0,str;
	
	store_score();

	//选择未使用的stmp标记
	ifstream archive_list;
	archive_list.open("archive/list.txt");
	while(archive_list >> stmp>>str);
	archive_list.close();
	stmp++;

	//将新文件名与分数写入目录
	ofstream achive_list;
	achive_list.open("archive/list.txt", ios::app);
	achive_list << stmp << " " << fraction << endl;
	archive_list.close();

	//创建新txt记录
	string ch = "archive/0.txt";
	ch[8] = stmp + '0';
	ofstream maptxt;
	maptxt.open(ch);
	maptxt << fraction <<" "<< hard_num<<endl;
	for(int i = 0; i < 30; i++)
	{
		for(int j = 0; j < 15; j++)
			maptxt << mapp[i][j] << " ";
		maptxt << endl;
	}
	maptxt.close();
}