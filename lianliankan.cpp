//大作业：连连看;

#include <graphics.h> //需要的头文件
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <mmsystem.h>
#include <mmsyscom.h>
#include "lianliankan.h"
#pragma comment(lib, "Winmm.lib")

IMAGE img[15];                          //储存动物图;
IMAGE base[2];                          //储存背景图;
IMAGE button[20];                       //储存一些按钮的图片;
IMAGE rank[10];                         //储存排名图片;
MOUSEMSG msg;                           //接受鼠标信息;
POINT begin = {-1, -1}, end = {-1, -1}; //存储鼠标坐标的结构体;
POINT temponce;                         //临时储存结构体;

int flag = 1;                                    //判断是第一次还是第二次点击鼠标;
int mode = 0;                                    //初始按钮;
int map[16][12] = {};                            //储存各个点的动物图;
int score = 0, temp = 0;                         //定义得分;
int num_wash = 1, num_hint = 2;                  //洗牌，提示的次数;
int flagmusic = 1;								 //前两个是判断音乐是否播放的flag;
int flag1 = 0, flag2 = 0, flagjudge = 0;         //前两个是判断是否打勾的flag，最后一个是来判断是否能够消去的flag;
int buffer = 1;                                  //是否保留数据，处理时间的flag;
int card = 140;                                  //存场上剩余卡数;
int flagclick = 0;                               //记录是否是第一次点击;
long now, start, first, second = 0, storage = 0; //处理时间的变量;

TCHAR scor[6] = {0}; //游戏数据变量,分数，提示数，洗牌数，时间;
TCHAR hin[2] = {'2'};
TCHAR wash[2] = {'1'};
TCHAR time1[5] = {'6', '0', '0', 's'};
TCHAR name[100] = {}; //存胜利者大名的;
struct info
{
    char name1[100];
    int score;
} list[100]; //定义用来存储六名幸运选手信息的结构体;

int main()
{
    initgraph(640, 480, SHOWCONSOLE); //创建窗口;
    imageload();                      //加载图片;
    gameload();                       //加载数据;
    printf("欢迎进入游戏，请开始您的游戏之旅\n");
    firstpage();  //加载第一页的内容;
    rearrange(0); //初始重排;
    while (1)     //采用循环使得能够不停的玩;
    {
        switch (mode)
        {
        case 0:
            firstpage(); //回到第一页
            break;
        case 1:
            start = clock() / 1000; //记录游戏开始时间;
            gamestart();            //开始游戏;
            closegraph();
            mode = 0; //模式归零;
            break;
        case 2:
            setting(); //进入设置界面;
            mode = 0;  //模式归零;
            break;
        case 3:
            ranklist();
            mode = 0; //模式归零;
            break;    //进入排行榜界面;
        case 4:
            exit(0); //退出游戏;
        }
    }
    return 0;
}
void playmusic()
{
    mciSendString("open ../resources/click.mp3 alias c", NULL, 0, NULL);
    mciSendString("play c", NULL, 0, NULL);
    Sleep(140);
    mciSendString("close c", NULL, 0, NULL);
}
void imageload()
{
    loadimage(&base[0], _T("../resources/背景.png"), 640, 480); //将图片存入img中;
    loadimage(&base[1], _T("../resources/base1.png"), 600, 40);
    loadimage(&img[0], _T("../resources/1.png"), 40, 40);
    loadimage(&img[1], _T("../resources/2.png"), 40, 40);
    loadimage(&img[2], _T("../resources/3.png"), 40, 40);
    loadimage(&img[3], _T("../resources/4.png"), 40, 40);
    loadimage(&img[4], _T("../resources/5.png"), 40, 40);
    loadimage(&img[5], _T("../resources/6.png"), 40, 40);
    loadimage(&img[6], _T("../resources/7.png"), 40, 40);
    loadimage(&img[7], _T("../resources/8.png"), 40, 40);
    loadimage(&img[8], _T("../resources/9.png"), 40, 40);
    loadimage(&img[9], _T("../resources/10.png"), 40, 40);
    loadimage(&img[10], _T("../resources/11.png"), 40, 40);
    loadimage(&img[11], _T("../resources/12.png"), 40, 40);
    loadimage(&img[12], _T("../resources/13.png"), 40, 40);
    loadimage(&img[13], _T("../resources/14.png"), 40, 40);
    loadimage(&img[14], _T("../resources/firstpage.png"), 640, 480);
    loadimage(&button[6], _T("../resources/musicsetting.png"), 640, 480);
    loadimage(&button[7], _T("../resources/SQUARE.png"), 40, 40);
    loadimage(&button[8], _T("../resources/tick.png"), 40, 50);
    loadimage(&button[9], _T("../resources/clock.png"), 40, 40);
    loadimage(&button[10], _T("../resources/score.png"), 40, 30);
    loadimage(&button[11], _T("../resources/hint.png"), 40, 30);
    loadimage(&button[12], _T("../resources/wash.png"), 40, 30);
    loadimage(&button[13], _T("../resources/escape.png"), 40, 30);
    loadimage(&button[14], _T("../resources/ask.png"), 640, 480);
    loadimage(&button[15], _T("../resources/washing.png"), 640, 180);
    loadimage(&rank[0], _T("../resources/win.png"), 640, 480);
    loadimage(&rank[1], _T("../resources/lose.png"), 640, 480);
    loadimage(&rank[2], _T("../resources/rankgold.png"), 80, 480);
}
void gameload()
{
    int k = 0;

    for (int i = 0; i < 16; i++) //将边缘初始化为0;
    {
        map[i][0] = -1;
        map[i][11] = -1;
    }
    for (int i = 0; i < 12; i++) //将边缘初始化为0;
    {
        map[0][i] = -1;
        map[15][i] = -1;
    }
    for (int i = 1; i <= 14; i++) //初始化顺序的图片位置;
    {
        for (int j = 1; j <= 10; j++)
        {
            map[i][j] = k;
        }
        k++;
    }
    hin[0] = '2'; //初始化游戏变量;
    wash[0] = '1';
    scor[0] = 0;
    scor[1] = 0;
    scor[2] = 0;
    scor[3] = 0;
}
void ranklist()
{
    initgraph(640, 480, SHOWCONSOLE);
    info temp;
    int n = 0, j = 0, i = 0, k = 0;
    FILE *fp;
    fp = fopen("../resources/rank.txt", "rb"); //读取resources文件夹里面的rank.txt文件;
    if (fp == NULL)                            //如果没找到，提示;
    {
        printf("暂无记录");
        return;
    }
    rewind(fp);
    while (!feof(fp)) //feof检查文件是否结束，遇到结束符，返回非零;
    {
        fscanf(fp, "%s %d\n", &list[i].name1, &list[i].score); //读取数据;
        i++;
    }
    for (j = 0; j < i - 1; j++)
    {
        for (k = 0; k < i - j - 1; k++)//冒泡排序,还排序了名字;
        {
            if ((list[k].score < list[k + 1].score) 
				|| (list[k].score == list[k + 1].score && strcmp(list[k + 1].name1, list[k].name1))) 
            {
                temp = list[k + 1];
                list[k + 1] = list[k];
                list[k] = temp;
            }
        }
    }
    fclose(fp);             //关闭文件;
    printf("点击可退出\n"); //提示用户;
    while (1)               //用图象展示;
    {
        BeginBatchDraw();
        putimage(0, 0, &rank[2]);
        sprintf(name, "%s %d", list[0].name1, list[0].score); //输出名字+得分;
        outtextxy(80, 20, name);
        sprintf(name, "%s %d", list[1].name1, list[1].score);
        outtextxy(80, 110, name);
        sprintf(name, "%s %d", list[2].name1, list[2].score);
        outtextxy(80, 200, name);
        sprintf(name, "%s %d", list[3].name1, list[3].score);
        outtextxy(80, 280, name);
        sprintf(name, "%s %d", list[4].name1, list[4].score);
        outtextxy(80, 350, name);
        sprintf(name, "%s %d", list[5].name1, list[5].score);
        outtextxy(80, 420, name);
        settextstyle(40, 0, _T("Consolas"));
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) //单击就可以退出;
            {
                break;
            }
        }
        EndBatchDraw();
    }
    return;
}
void newgraph() //询问是否要保留数据;
{
    while (1)
    {
        BeginBatchDraw();
        putimage(0, 0, &button[14]);
        if (MouseHit()) //检测是否有鼠标操作;
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN && abs(msg.x - 170) <= 20 && abs(msg.y - 270) <= 20) //如果是要保存数据;
            {
                playmusic();
                buffer = 0;
                break;
            }
            else if (msg.uMsg == WM_LBUTTONDOWN && abs(msg.x - 450) <= 20 && abs(msg.y - 270) <= 20) ///如果是不保存数据;
            {
                playmusic();
                gameload();
                rearrange(0);
                begin.x = -1;
                end.x = -1;
                score = 0;
                num_wash = 1;
                num_hint = 2;
                card = 140;
                storage = 0;
                break;
            }
        }
        EndBatchDraw();
    }
}
void firstpage() //展示首页的内容;
{
    mode = 0;
    initgraph(640, 480, SHOWCONSOLE);
    if (flagmusic) //判断是否播放音乐;
    {
        mciSendString("open ../resources/1.mp3 alias a", NULL, 0, NULL);
        mciSendString("play a repeat", NULL, 0, NULL);
    }
    while (1)
    {
        BeginBatchDraw();
        putimage(0, 0, &img[14], SRCPAINT);
        if (MouseHit())
        {
            msg = GetMouseMsg();
            begin.y = msg.x;
            begin.x = msg.y;

            if (msg.uMsg == WM_LBUTTONDOWN && abs(begin.y - 300) <= 75 && abs(begin.x - 335) <= 135)
            {
                playmusic();
                mode = modeselect(begin); //选择模式;
            }
            if (mode) //如果点击在范围内，跳出;
                break;
        }
        EndBatchDraw();
    }
}
int modeselect(POINT begin)
{
    if (abs(begin.x - 230) <= 30) //判断第一页的选中模式;
        return 1;
    else if (abs(begin.x - 300) <= 30)
        return 2;
    else if (abs(begin.x - 370) <= 30)
        return 3;
    else if (abs(begin.x - 440) <= 30)
        return 4;
    else
        return 0;
}
void nameyourself() //展示胜利图片;
{
    while (1)
    {
        BeginBatchDraw();
        putimage(0, 0, &rank[0]);
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) //单击就输入名字;
            {
                playmusic();
                break;
            }
        }
        EndBatchDraw();
    }
    FILE *fp;
    printf("大侠请输入您的大名：");
    scanf("%s", &name);
    fp = fopen("../resources/rank.txt", "a");
    fprintf(fp, "%s %d\n", name, score); //存进文件中;
    fclose(fp);
    return;
}
void youlose()
{
    while (1)
    {
        putimage(0, 0, &rank[1]); //单击回到首页;
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                break;
            }
        }
    }
    return;
}
void gamestart()
{
    srand((unsigned)time(NULL));
    initgraph(640, 480, SHOWCONSOLE);
    while (1)
    {
        BeginBatchDraw();
        temp = score;
        sprintf_s(scor, "%d", temp); //输入成绩;
        if (buffer)                  //为不保存数据的时间情况;
            now = clock() / 1000;
        else //为保存数据的时间情况;
        {
            start = storage / 1000;
            buffer = 1;
            now = clock() / 1000;
        }
        temp = 360 - (now - start);          //计算时间差;
        settextstyle(40, 0, _T("Consolas")); //选择字体类型和大小;
        sprintf_s(time1, "%ds", temp);       //输入时间;

        putimage(0, 40, &base[0]);
        putimage(40, 0, &base[1], SRCAND); //放图;
        putimage(140, 5, &button[10]);
        putimage(260, 5, &button[11]);
        putimage(380, 5, &button[12]);
        putimage(580, 5, &button[13]);
        putimage(0, 0, &button[9]);
        outtextxy(40, 0, time1); //输出时间;
        outtextxy(180, 0, scor); //输出成绩;
        outtextxy(300, 0, hin);  //输出提示次数;
        outtextxy(420, 0, wash); //输出洗牌次数;
        for (int i = 1; i <= 15; i++)
        {
            for (int j = 1; j <= 11; j++)
            {
                if (map[i][j] != -1)
                    putimage(i * 40, j * 40, &img[map[i][j]]); //放图;
                else
                    ;
            }
        }
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                flagclick = 1;
                playmusic();
                if (abs(msg.x - 600) <= 20 && abs(msg.y - 20) <= 15) //如果要退出，进入退出界面;
                {
                    newgraph();
                    break;
                }
                else if (abs(msg.x - 400) <= 20 && abs(msg.y - 20) <= 15 && num_wash > 0) //洗牌操作;
                {
                    rearrange(1);
                    num_wash--;
                    wash[0]--;
                }
                else if (abs(msg.x - 280) <= 20 && abs(msg.y - 20) <= 15 && num_hint > 0) //提示操作;
                {
                    hint(0);
                    num_hint--;
                    hin[0]--;
                }
                if (flag) //获得第一个坐标;
                {
                    begin.x = msg.x / 40;
                    begin.y = msg.y / 40;

                    flag = 0;
                }
                else if (!flag) //获得第二个坐标;
                {
                    end.x = msg.x / 40;
                    end.y = msg.y / 40;
                    first = clock(); //并且获得此时的时间;
                    flag = 1;
                }
                if (hint(1)) //判断是否还有剩余图案可消去;
                    rearrange(1);
            }
            flagjudge = 0;         //初始化;
            if (!demo(begin, end)) //判断可否消去;
            {
                if (begin.x != -1 && end.x == -1) //如果是只点了第一个的情况，flag改为第二个;
                {
                    flag = 0;
                }
                else if (begin.x == end.x && end.y == begin.y) //如果两次点击相同，则取消选中,flag改为第一个;
                {
                    flag = 1;
                    begin.x = -1;
                    begin.y = -1;
                    end.x = -1;
                    end.y = -1;
                }
                else if (begin.x != -1 && end.x == -1) //如果第二个点击了空白;
                {

                    begin = end;
                    end.x = -1;
                    flag = 0;
                }
                else if (flagjudge) //如果是有情况,flag指向第一个,图案数减2;
                {
                    flag = 1;
                    card -= 2;
                    begin.x = -1;
                    begin.y = -1;
                    end.x = -1;
                    end.y = -1;
                }

                else //其他情况则把第二个坐标给第一个，flag指向第二个;
                {
                    begin = end;
                    flag = 0;
                    end.x = -1;
                }
            }
        }
        if (map[begin.x][begin.y] != -1)                                  //如果点到空白则不显示;
            putimage((begin.x) * 40, (begin.y) * 40, &button[7], SRCAND); //点击输出框;
        if (map[end.x][end.y] != -1)
            putimage((end.x) * 40, (end.y) * 40, &button[7], SRCAND);
        EndBatchDraw();
        if (card == 0 && temp != 0) //如果没有牌且时间不为0,胜利;
        {
            nameyourself();
            break;
        }
        if (temp == 0) //如果时间为0,失败;
        {
            youlose();
            break;
        }
    }
}
int hint(int n) //一个函数既可以用来检测有没有剩余牌，也可用来提示;
{
    POINT a, b;
	int m=0;
    for (int i = 1; i < 15; i++) //遍历所有情况;
    {
        for (int j = 1; j < 11; j++)
        {
            for (int k = 1; k < 15; k++)
            {
                for (int l = 1; l < 11; l++)
                {
                    a.x = i;
                    a.y = j;
                    b.x = k;
                    b.y = l;
                    if (a.x == b.x && a.y == b.y) //如果相等不考虑;
                    {
                        continue;
                    }
                    if (!n && map[a.x][a.y] != -1 && map[a.x][a.y] == map[b.x][b.y] && (horizon(b, a) || vertical(b, a) || turn_once(b, a) || turn_twice(b, a))) //把易判断的放在前面，有利于增快判断速度,且做提示作用;
                    {
                        while (m < 1000)
                        {
                            BeginBatchDraw();
                            putimage(i * 40, j * 40, &button[7], SRCAND);
                            putimage(k * 40, l * 40, &button[7], SRCAND);
                            m++;
                            EndBatchDraw();
                        }
                        return 0;
                    }
                    else if (map[a.x][a.y] != -1 && map[a.x][a.y] == map[b.x][b.y] && (horizon(a, b) || vertical(a, b) || turn_once(a, b) || turn_twice(a, b))) //这是判断有无可以相连的;
                        return 0;
                }
            }
        }
    }
    return 1;
}
int demo(POINT begin, POINT end) //判断是否可以消去;
{
    temponce = begin;
    if (begin.x == -1 && end.x == -1) //如果是初始情况，返回1;
        return 1;
    if (begin.x != end.x || begin.y != end.y) //如果有一方不等，则进入判断;
    {
        if (map[begin.x][begin.y] == -1 && map[end.x][end.y] == -1) //若有两个无图案;
        {
            flag = 0;
            flagjudge = 0;
            return 1;
        }
        else if (map[begin.x][begin.y] != map[end.x][end.y]) //若两个图案不等;
        {
            flag = 1;
            begin.x = -1;
            end.x = -1;
            begin.y = -1;
            end.y = -1;
            return 0;
        }
        else if (map[begin.x][begin.y] == map[end.x][end.y]) //若图案相等;
        {
            if ((horizon(begin, end) || vertical(begin, end) || turn_once(begin, end) || turn_twice(begin, end)) && abs(second - first) / 1000 <= 2) //且可以消去，两次消去时间间隔小于2秒;
            {
                map[temponce.x][temponce.y] = -1;
                map[end.x][end.y] = -1;
                flag = 1;
                second = first;
                flagjudge = 1;
                score += 4;
            }
            else if (horizon(begin, end) || vertical(begin, end) || turn_once(begin, end) || turn_twice(begin, end)) //大于两秒;
            {
                map[temponce.x][temponce.y] = -1;
                map[end.x][end.y] = -1;
                flag = 1;
                second = first;
                flagjudge = 1;
                score += 2;
            }
        }
    }
    return 0;
}
int isBlocked(int x, int y) //判断是否有阻碍;
{
    if (map[x][y] == -1) //如果无图案，则没有阻碍;
        return 0;
    else
        return 1;
}
bool horizon(POINT begin, POINT end) //判断水平方向;
{
    if (begin.x == end.x && begin.y == end.y) //不能点击同一个;
    {
        return false;
    }
    if (begin.x != end.x) //是否满足在同一直线上：
    {
        return false;
    }
    int m_min = min(begin.y, end.y); //取最值;
    int m_max = max(begin.y, end.y);
    for (int i = m_min + 1; i < m_max; i++) //判断中间有无阻碍;
    {
        if (isBlocked(begin.x, i))
        {
            return false;
        }
    }
    return true;
}
bool vertical(POINT begin, POINT end) //垂直方向;
{
    if (begin.x == end.x && begin.y == end.y) //不能点击同一个;
    {
        return false;
    }
    if (begin.y != end.y) //是否在一直线上;
    {
        return false;
    }
    int m_min = min(begin.x, end.x); //取最值;
    int m_max = max(begin.x, end.x);
    for (int i = m_min + 1; i < m_max; i++) //判断中间有无阻碍;
    {
        if (isBlocked(i, begin.y))
        {
            return false;
        }
    }
    return true;
}
bool turn_once(POINT begin, POINT end)
{
    int temp1 = begin.x;
	int temp2 = begin.y;
    if (begin.x == end.x && begin.y == end.y) //不能为同一点;
    {
        return false;
    }
    for (int i = temp1 - 1; i >= 0; i--) //判断方块纵向向上方向有无水平消去的可能;
    {
        begin.x = i;
        if (isBlocked(i, begin.y))
            break;
        if (horizon(begin, end))
            return 1;
    }
    for (int i = temp1 + 1; i <= 15; i++) //判断方块纵向向下方向上有无水平消去可能;
    {
        begin.x = i;
        if (isBlocked(i, begin.y))
            break;
        if (horizon(begin, end))
            return 1;
    }
    begin.x = temp1;
    for (int i = temp2 - 1; i >= 0; i--) //判断方块横向方向向左方向有无消去可能;
    {
        begin.y = i;
        if (isBlocked(begin.x, i))
            break;
        if (vertical(begin, end))
            return 1;
    }
    for (int i = temp2 + 1; i <= 13; i++) //判断方块横向方向向右有无消去可能;
    {
        begin.y = i;
        if (isBlocked(begin.x, i))
            break;
        if (vertical(begin, end))
            return 1;
    }
    return 0;
}
bool turn_twice(POINT begin, POINT end)
{
    int temp1=begin.x;
	int temp2=begin.y;
	if (begin.x == end.x && begin.y == end.y) //不能为同一点;
        return 0;
    for (int i = temp1 - 1; i >= 0; i--) //同turn_once标注的，判断是否可能经过一次转折消去;
    {
        begin.x = i;
        if (isBlocked(i, begin.y))
            break;
        if (turn_once(begin, end))
            return 1;
    }
    for (int i = temp1 + 1; i <= 15; i++) //下面循环均同上;
    {
        begin.x = i;
        if (isBlocked(i, begin.y))
            break;
        if (turn_once(begin, end))
            return 1;
    }
    begin.x = temp1;
    for (int i = temp2 + 1; i <= 13; i++)
    {
        begin.y = i;
        if (isBlocked(begin.x, i))
            break;
        if (turn_once(begin, end))
            return 1;
    }
    for (int i = temp2 - 1; i >= 0; i--)
    {
        begin.y = i;
        if (isBlocked(begin.x, i))
            break;
        if (turn_once(begin, end))
            return 1;
    }
    return 0;
}
int judge() //判断是否有10个相连
{
    int num = 0;
    for (int i = 1; i <= 14; i++) //遍历数组，寻找相邻点;
        for (int j = 1; j <= 12; j++)
        {
            if (map[i][j] != -1 && (map[i - 1][j] == map[i][j] || map[i + 1][j] == map[i][j] || map[i][j - 1] == map[i][j] || map[i][j + 1] == map[i][j]))
                num++;
        }
    if (num < 10) //若小于10个，重排，直到返回值为1为止;
    {
        do
        {
            rearrange(0);
        } while (!judge());
    }
    return 1;
}
void rearrange(int flag)
{
    int i = 0;
    srand(GetTickCount());
    while (i < 100) //尽可能打乱,循环1000次;
    {
        for (int i = 1; i <= 14; i++)
            for (int j = 1; j <= 10; j++)
            {
                int temp1 = map[i][j];
                int col = rand() % 10 + 1;
                int row = rand() % 14 + 1;
                if (!flag) //为完整的重排，包括不保存数据的重排;
                {
                    if (temp1 == -1)
                        continue;
                    if (map[row][col] == -1 || map[i][j] == -1)
                        continue;
                    else
                    {
                        map[i][j] = map[row][col]; //两个数组都随机放置;
                        map[row][col] = temp1;
                    }
                }
                else //游戏中的重排;
                {
                    if (map[i][j] != -1 && map[row][col] != -1)
                    {
                        map[i][j] = map[row][col]; //两个数组都随机放置;
                        map[row][col] = temp1;
                    }
                }
            }
        i++;
    }
}
void setting()
{
    initgraph(640, 480, SHOWCONSOLE);
    while (1)
    {
        BeginBatchDraw();
        putimage(0, 0, &button[6], SRCPAINT);
        if (!flag1) //如果点击，打勾;
        {
            putimage(300, 165, &button[8], SRCAND);
        }
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN && msg.x <= 80 && msg.y <= 80)
            {
                playmusic();
                break;
            }
            else if (msg.uMsg == WM_LBUTTONDOWN && abs(msg.x - 320) <= 20 && abs(msg.y - 195) <= 20)
            {
                playmusic();
                flagmusic = !flagmusic;
                if (!flagmusic) //判断是否放音乐;
                    mciSendString("close a", NULL, 0, NULL);
                else
                {
                    mciSendString("open ../resources/1.mp3 alias a", NULL, 0, NULL);
                    mciSendString("play a", NULL, 0, NULL);
                }
                flag1 = !flag1;
            }
        }
        EndBatchDraw();
    }
}