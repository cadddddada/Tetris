#ifndef HEADER_H
#define HEADER_H
#include<stdio.h>
#include<graphics.h>
#include<easyx.h>
#include<bits/stdc++.h>
#include<random>
#include<io.h>

using namespace std;

#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#define mplus_hzk_12 mplus_hzk_12

//全局参数
extern int mapp[2][31][16];
extern int fraction[2];
extern int hard_num;
extern int max_score;
extern int resurrection_coin;

//选择界面打印组件调用参数
extern int score_elem_len;
extern int score_elem[6][2];
const pair<int, int> elem_axis[6] = { {100,146},{100,186},{100,226},{250,146},{250,186},{250,226} };
const pair<int, int> shape[7][4][4] = {
    {{{0,0},{0,1},{1,0},{1,1}},{{0,0},{0,1},{1,0},{1,1}},{{0,0},{0,1},{1,0},{1,1}},{{0,0},{0,1},{1,0},{1,1}}},
    {{{0,0},{1,0},{2,0},{3,0}},{{0,0},{0,1},{0,2},{0,3}},{{0,0},{1,0},{2,0},{3,0}},{{0,0},{0,1},{0,2},{0,3}}},
    {{{0,1},{0,2},{1,0},{1,1}},{{0,0},{1,0},{1,1},{2,1}},{{0,1},{0,2},{1,0},{1,1}},{{0,0},{1,0},{1,1},{2,1}}},
    {{{0,0},{0,1},{1,1},{1,2}},{{0,1},{1,0},{1,1},{2,0}},{{0,0},{0,1},{1,1},{1,2}},{{0,1},{1,0},{1,1},{2,0}}},
    {{{0,0},{1,0},{2,0},{2,1}},{{0,0},{0,1},{0,2},{1,0}},{{0,0},{0,1},{1,1},{2,1}},{{0,2},{1,0},{1,1},{1,2}}},
    {{{0,1},{1,1},{2,0},{2,1}},{{0,0},{1,0},{1,1},{1,2}},{{0,0},{0,1},{1,0},{2,0}},{{0,0},{0,1},{0,2},{1,2}}},
    {{{0,0},{0,1},{0,2},{1,1}},{{0,1},{1,0},{1,1},{2,1}},{{0,1},{1,0},{1,1},{1,2}},{{0,0},{1,0},{1,1},{2,0}}} };
const int color_elem[8][3] = {
    {0,0,0}, {241, 112, 125},{172, 94, 116},{242, 222, 189},
    {241, 184, 241},{243, 215, 81},{255, 132, 68},{180, 144, 160} };

//游戏界面
int start_screen(int x, int y);
int archive_screen(int x, int y);
bool game_screen(int mode);
bool stop_screen(int x, int y);
int end_screen(int x, int y, int mode_t);
int mode_screen();

//txt数据处理组件
bool set_map(int style);
void store_score();
void archiving();
void delete_the_archive(int map_name);

//打印组件
void button(int x, int y, int w, int h, const char* ch);
void arch_scr(int x, int y);
void general1_scr(int x, int y,int style);
void general2_scr(int x, int y, int style);
void draw_map(int x, int y, int user);
void draw_small_windows(int x, int y, int shapenum, int style);
void draw_fraction(int x, int y, int user);
void Two_player_win_display(int x, int y, int fra1, int fra2);
void error_scr(int x, int y);
void instructions(int x, int y);

//鼠标与键盘识别组件
int general1_operate_identify(int x,int y,int style);
int arch_operate_identify(int x,int y);
int general2_operate_identify(int x, int y,int style);
int Key_presses(int x[], int y[], int shapenum[], int style[], int tip[], int time, int mode);

//地图数组处理组件
bool boundary_check(int x, int y, pair<int, int> stmp);
bool check(int x, int y, int shapenum, int style, int user);
void del_line(int x, int user);
int line_check(int user);
bool end_check(int user);
void dispose_shape(int x, int y, int shapenum, int style, bool tip, int user);
bool resurrection(int x, int y);
void read_score_txt();

//存档加载组件
void archive_processing(int x, int y);


#endif