#include"header.h"
using namespace std;

int mapp[2][31][16];
int fraction[2];
int hard_num;
int max_score;
int resurrection_coin;

void read_score_txt()
{
	ifstream score_list;//读取最高分
	score_list.open("archive/score.txt");
	if(!(score_list >> max_score >> resurrection_coin))
		max_score = 0, resurrection_coin = 20,cout<<"reset"<<endl;
	score_list.close();
}

bool set_map(int style)//初始化游戏地图，style=-1 means new game, style=0 means exit, other means open file
{
	if(style)
	{
		read_score_txt();

		if(style == -1)
		{
			CreateDirectory("archive", NULL);
			//system("mkdir archive"); 不使用此函数是因为创建失败时会显示报错信息

			fraction[0] =fraction[1]= 0;
			hard_num = 1;
			memset(mapp, 0, sizeof mapp);//初始化地图为0
			return true;
		}
		else
		{
			string ch = "archive/", ch2 = ".txt";//从记录中读取
			ch += to_string(style);
			ch += ch2;
			ifstream maptxt;
			maptxt.open(ch);
			maptxt >> fraction[0] >>fraction[1]>> hard_num;
			for(int k = 0; k < 2; k++)
				for(int i = 0; i < 30; i++)
					for(int j = 0; j < 15; j++)
						maptxt >> mapp[k][i][j];
			maptxt.close();

			delete_the_archive(style);//删除记录
			remove(ch.c_str());
			return true;
		}
	}
	return false;
}

void store_score()//存储最高分
{
		ofstream score_list;
		score_list.open("archive/score.txt");
		score_list << max(max(fraction[0], fraction[1]),max_score) << endl;
		score_list<< resurrection_coin<<endl;
		score_list.close();
}

void archiving()//保存游戏记录
{
	int stmp = 0, str;

	store_score();

	//选择未使用的stmp标记
	ifstream archive_list;
	archive_list.open("archive/list.txt");
	while(archive_list >> stmp >> str);
	archive_list.close();
	stmp++;

	//将新文件名与分数写入目录
	ofstream achive_list;
	achive_list.open("archive/list.txt", ios::app);
	achive_list << stmp << " " << max(fraction[0], fraction[1]) << endl;
	archive_list.close();

	//创建新txt记录
	string ch = "archive/",ch2=".txt";
	ch += to_string(stmp);
	ch += ch2;
	ofstream maptxt;
	maptxt.open(ch);
	maptxt << fraction[0] <<" "<<fraction[1]<<" "<< hard_num << endl;
	for(int k = 0; k < 2; k++)
		for(int i = 0; i < 30; i++)
		{
			for(int j = 0; j < 15; j++)
				maptxt << mapp[k][i][j] << " ";
			maptxt << endl;
		}
	maptxt.close();
}

void delete_the_archive(int map_name)
{
	vector<pair<int, int>> arch_elem;//获取list.txt到elem
	int p, q,stmp;
	ifstream archive_list;
	archive_list.open("archive/list.txt");
	while(archive_list >> p >> q)
	{
		arch_elem.push_back({ p,q });
		if(p == map_name)
			stmp = arch_elem.size()-1;
	}
	archive_list.close();

	arch_elem.erase(arch_elem.begin()+stmp);//删除指定记录数据

	//将新文件名与分数写入目录
	ofstream achive_list;
	achive_list.open("archive/list.txt");
	for(auto i:arch_elem)
		achive_list << i.first << " " << i.second << endl;
	archive_list.close();

}