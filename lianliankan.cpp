//����ҵ��������;

#include <graphics.h> //��Ҫ��ͷ�ļ�
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <mmsystem.h>
#include <mmsyscom.h>
#include "lianliankan.h"
#pragma comment(lib, "Winmm.lib")

IMAGE img[15];                          //���涯��ͼ;
IMAGE base[2];                          //���汳��ͼ;
IMAGE button[20];                       //����һЩ��ť��ͼƬ;
IMAGE rank[10];                         //��������ͼƬ;
MOUSEMSG msg;                           //���������Ϣ;
POINT begin = {-1, -1}, end = {-1, -1}; //�洢�������Ľṹ��;
POINT temponce;                         //��ʱ����ṹ��;

int flag = 1;                                    //�ж��ǵ�һ�λ��ǵڶ��ε�����;
int mode = 0;                                    //��ʼ��ť;
int map[16][12] = {};                            //���������Ķ���ͼ;
int score = 0, temp = 0;                         //����÷�;
int num_wash = 1, num_hint = 2;                  //ϴ�ƣ���ʾ�Ĵ���;
int flagmusic = 1;								 //ǰ�������ж������Ƿ񲥷ŵ�flag;
int flag1 = 0, flag2 = 0, flagjudge = 0;         //ǰ�������ж��Ƿ�򹴵�flag�����һ�������ж��Ƿ��ܹ���ȥ��flag;
int buffer = 1;                                  //�Ƿ������ݣ�����ʱ���flag;
int card = 140;                                  //�泡��ʣ�࿨��;
int flagclick = 0;                               //��¼�Ƿ��ǵ�һ�ε��;
long now, start, first, second = 0, storage = 0; //����ʱ��ı���;

TCHAR scor[6] = {0}; //��Ϸ���ݱ���,��������ʾ����ϴ������ʱ��;
TCHAR hin[2] = {'2'};
TCHAR wash[2] = {'1'};
TCHAR time1[5] = {'6', '0', '0', 's'};
TCHAR name[100] = {}; //��ʤ���ߴ�����;
struct info
{
    char name1[100];
    int score;
} list[100]; //���������洢��������ѡ����Ϣ�Ľṹ��;

int main()
{
    initgraph(640, 480, SHOWCONSOLE); //��������;
    imageload();                      //����ͼƬ;
    gameload();                       //��������;
    printf("��ӭ������Ϸ���뿪ʼ������Ϸ֮��\n");
    firstpage();  //���ص�һҳ������;
    rearrange(0); //��ʼ����;
    while (1)     //����ѭ��ʹ���ܹ���ͣ����;
    {
        switch (mode)
        {
        case 0:
            firstpage(); //�ص���һҳ
            break;
        case 1:
            start = clock() / 1000; //��¼��Ϸ��ʼʱ��;
            gamestart();            //��ʼ��Ϸ;
            closegraph();
            mode = 0; //ģʽ����;
            break;
        case 2:
            setting(); //�������ý���;
            mode = 0;  //ģʽ����;
            break;
        case 3:
            ranklist();
            mode = 0; //ģʽ����;
            break;    //�������а����;
        case 4:
            exit(0); //�˳���Ϸ;
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
    loadimage(&base[0], _T("../resources/����.png"), 640, 480); //��ͼƬ����img��;
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

    for (int i = 0; i < 16; i++) //����Ե��ʼ��Ϊ0;
    {
        map[i][0] = -1;
        map[i][11] = -1;
    }
    for (int i = 0; i < 12; i++) //����Ե��ʼ��Ϊ0;
    {
        map[0][i] = -1;
        map[15][i] = -1;
    }
    for (int i = 1; i <= 14; i++) //��ʼ��˳���ͼƬλ��;
    {
        for (int j = 1; j <= 10; j++)
        {
            map[i][j] = k;
        }
        k++;
    }
    hin[0] = '2'; //��ʼ����Ϸ����;
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
    fp = fopen("../resources/rank.txt", "rb"); //��ȡresources�ļ��������rank.txt�ļ�;
    if (fp == NULL)                            //���û�ҵ�����ʾ;
    {
        printf("���޼�¼");
        return;
    }
    rewind(fp);
    while (!feof(fp)) //feof����ļ��Ƿ���������������������ط���;
    {
        fscanf(fp, "%s %d\n", &list[i].name1, &list[i].score); //��ȡ����;
        i++;
    }
    for (j = 0; j < i - 1; j++)
    {
        for (k = 0; k < i - j - 1; k++)//ð������,������������;
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
    fclose(fp);             //�ر��ļ�;
    printf("������˳�\n"); //��ʾ�û�;
    while (1)               //��ͼ��չʾ;
    {
        BeginBatchDraw();
        putimage(0, 0, &rank[2]);
        sprintf(name, "%s %d", list[0].name1, list[0].score); //�������+�÷�;
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
            if (msg.uMsg == WM_LBUTTONDOWN) //�����Ϳ����˳�;
            {
                break;
            }
        }
        EndBatchDraw();
    }
    return;
}
void newgraph() //ѯ���Ƿ�Ҫ��������;
{
    while (1)
    {
        BeginBatchDraw();
        putimage(0, 0, &button[14]);
        if (MouseHit()) //����Ƿ���������;
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN && abs(msg.x - 170) <= 20 && abs(msg.y - 270) <= 20) //�����Ҫ��������;
            {
                playmusic();
                buffer = 0;
                break;
            }
            else if (msg.uMsg == WM_LBUTTONDOWN && abs(msg.x - 450) <= 20 && abs(msg.y - 270) <= 20) ///����ǲ���������;
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
void firstpage() //չʾ��ҳ������;
{
    mode = 0;
    initgraph(640, 480, SHOWCONSOLE);
    if (flagmusic) //�ж��Ƿ񲥷�����;
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
                mode = modeselect(begin); //ѡ��ģʽ;
            }
            if (mode) //�������ڷ�Χ�ڣ�����;
                break;
        }
        EndBatchDraw();
    }
}
int modeselect(POINT begin)
{
    if (abs(begin.x - 230) <= 30) //�жϵ�һҳ��ѡ��ģʽ;
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
void nameyourself() //չʾʤ��ͼƬ;
{
    while (1)
    {
        BeginBatchDraw();
        putimage(0, 0, &rank[0]);
        if (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) //��������������;
            {
                playmusic();
                break;
            }
        }
        EndBatchDraw();
    }
    FILE *fp;
    printf("�������������Ĵ�����");
    scanf("%s", &name);
    fp = fopen("../resources/rank.txt", "a");
    fprintf(fp, "%s %d\n", name, score); //����ļ���;
    fclose(fp);
    return;
}
void youlose()
{
    while (1)
    {
        putimage(0, 0, &rank[1]); //�����ص���ҳ;
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
        sprintf_s(scor, "%d", temp); //����ɼ�;
        if (buffer)                  //Ϊ���������ݵ�ʱ�����;
            now = clock() / 1000;
        else //Ϊ�������ݵ�ʱ�����;
        {
            start = storage / 1000;
            buffer = 1;
            now = clock() / 1000;
        }
        temp = 360 - (now - start);          //����ʱ���;
        settextstyle(40, 0, _T("Consolas")); //ѡ���������ͺʹ�С;
        sprintf_s(time1, "%ds", temp);       //����ʱ��;

        putimage(0, 40, &base[0]);
        putimage(40, 0, &base[1], SRCAND); //��ͼ;
        putimage(140, 5, &button[10]);
        putimage(260, 5, &button[11]);
        putimage(380, 5, &button[12]);
        putimage(580, 5, &button[13]);
        putimage(0, 0, &button[9]);
        outtextxy(40, 0, time1); //���ʱ��;
        outtextxy(180, 0, scor); //����ɼ�;
        outtextxy(300, 0, hin);  //�����ʾ����;
        outtextxy(420, 0, wash); //���ϴ�ƴ���;
        for (int i = 1; i <= 15; i++)
        {
            for (int j = 1; j <= 11; j++)
            {
                if (map[i][j] != -1)
                    putimage(i * 40, j * 40, &img[map[i][j]]); //��ͼ;
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
                if (abs(msg.x - 600) <= 20 && abs(msg.y - 20) <= 15) //���Ҫ�˳��������˳�����;
                {
                    newgraph();
                    break;
                }
                else if (abs(msg.x - 400) <= 20 && abs(msg.y - 20) <= 15 && num_wash > 0) //ϴ�Ʋ���;
                {
                    rearrange(1);
                    num_wash--;
                    wash[0]--;
                }
                else if (abs(msg.x - 280) <= 20 && abs(msg.y - 20) <= 15 && num_hint > 0) //��ʾ����;
                {
                    hint(0);
                    num_hint--;
                    hin[0]--;
                }
                if (flag) //��õ�һ������;
                {
                    begin.x = msg.x / 40;
                    begin.y = msg.y / 40;

                    flag = 0;
                }
                else if (!flag) //��õڶ�������;
                {
                    end.x = msg.x / 40;
                    end.y = msg.y / 40;
                    first = clock(); //���һ�ô�ʱ��ʱ��;
                    flag = 1;
                }
                if (hint(1)) //�ж��Ƿ���ʣ��ͼ������ȥ;
                    rearrange(1);
            }
            flagjudge = 0;         //��ʼ��;
            if (!demo(begin, end)) //�жϿɷ���ȥ;
            {
                if (begin.x != -1 && end.x == -1) //�����ֻ���˵�һ���������flag��Ϊ�ڶ���;
                {
                    flag = 0;
                }
                else if (begin.x == end.x && end.y == begin.y) //������ε����ͬ����ȡ��ѡ��,flag��Ϊ��һ��;
                {
                    flag = 1;
                    begin.x = -1;
                    begin.y = -1;
                    end.x = -1;
                    end.y = -1;
                }
                else if (begin.x != -1 && end.x == -1) //����ڶ�������˿հ�;
                {

                    begin = end;
                    end.x = -1;
                    flag = 0;
                }
                else if (flagjudge) //����������,flagָ���һ��,ͼ������2;
                {
                    flag = 1;
                    card -= 2;
                    begin.x = -1;
                    begin.y = -1;
                    end.x = -1;
                    end.y = -1;
                }

                else //���������ѵڶ����������һ����flagָ��ڶ���;
                {
                    begin = end;
                    flag = 0;
                    end.x = -1;
                }
            }
        }
        if (map[begin.x][begin.y] != -1)                                  //����㵽�հ�����ʾ;
            putimage((begin.x) * 40, (begin.y) * 40, &button[7], SRCAND); //��������;
        if (map[end.x][end.y] != -1)
            putimage((end.x) * 40, (end.y) * 40, &button[7], SRCAND);
        EndBatchDraw();
        if (card == 0 && temp != 0) //���û������ʱ�䲻Ϊ0,ʤ��;
        {
            nameyourself();
            break;
        }
        if (temp == 0) //���ʱ��Ϊ0,ʧ��;
        {
            youlose();
            break;
        }
    }
}
int hint(int n) //һ�������ȿ������������û��ʣ���ƣ�Ҳ��������ʾ;
{
    POINT a, b;
	int m=0;
    for (int i = 1; i < 15; i++) //�����������;
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
                    if (a.x == b.x && a.y == b.y) //�����Ȳ�����;
                    {
                        continue;
                    }
                    if (!n && map[a.x][a.y] != -1 && map[a.x][a.y] == map[b.x][b.y] && (horizon(b, a) || vertical(b, a) || turn_once(b, a) || turn_twice(b, a))) //�����жϵķ���ǰ�棬�����������ж��ٶ�,������ʾ����;
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
                    else if (map[a.x][a.y] != -1 && map[a.x][a.y] == map[b.x][b.y] && (horizon(a, b) || vertical(a, b) || turn_once(a, b) || turn_twice(a, b))) //�����ж����޿���������;
                        return 0;
                }
            }
        }
    }
    return 1;
}
int demo(POINT begin, POINT end) //�ж��Ƿ������ȥ;
{
    temponce = begin;
    if (begin.x == -1 && end.x == -1) //����ǳ�ʼ���������1;
        return 1;
    if (begin.x != end.x || begin.y != end.y) //�����һ�����ȣ�������ж�;
    {
        if (map[begin.x][begin.y] == -1 && map[end.x][end.y] == -1) //����������ͼ��;
        {
            flag = 0;
            flagjudge = 0;
            return 1;
        }
        else if (map[begin.x][begin.y] != map[end.x][end.y]) //������ͼ������;
        {
            flag = 1;
            begin.x = -1;
            end.x = -1;
            begin.y = -1;
            end.y = -1;
            return 0;
        }
        else if (map[begin.x][begin.y] == map[end.x][end.y]) //��ͼ�����;
        {
            if ((horizon(begin, end) || vertical(begin, end) || turn_once(begin, end) || turn_twice(begin, end)) && abs(second - first) / 1000 <= 2) //�ҿ�����ȥ��������ȥʱ����С��2��;
            {
                map[temponce.x][temponce.y] = -1;
                map[end.x][end.y] = -1;
                flag = 1;
                second = first;
                flagjudge = 1;
                score += 4;
            }
            else if (horizon(begin, end) || vertical(begin, end) || turn_once(begin, end) || turn_twice(begin, end)) //��������;
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
int isBlocked(int x, int y) //�ж��Ƿ����谭;
{
    if (map[x][y] == -1) //�����ͼ������û���谭;
        return 0;
    else
        return 1;
}
bool horizon(POINT begin, POINT end) //�ж�ˮƽ����;
{
    if (begin.x == end.x && begin.y == end.y) //���ܵ��ͬһ��;
    {
        return false;
    }
    if (begin.x != end.x) //�Ƿ�������ͬһֱ���ϣ�
    {
        return false;
    }
    int m_min = min(begin.y, end.y); //ȡ��ֵ;
    int m_max = max(begin.y, end.y);
    for (int i = m_min + 1; i < m_max; i++) //�ж��м������谭;
    {
        if (isBlocked(begin.x, i))
        {
            return false;
        }
    }
    return true;
}
bool vertical(POINT begin, POINT end) //��ֱ����;
{
    if (begin.x == end.x && begin.y == end.y) //���ܵ��ͬһ��;
    {
        return false;
    }
    if (begin.y != end.y) //�Ƿ���һֱ����;
    {
        return false;
    }
    int m_min = min(begin.x, end.x); //ȡ��ֵ;
    int m_max = max(begin.x, end.x);
    for (int i = m_min + 1; i < m_max; i++) //�ж��м������谭;
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
    if (begin.x == end.x && begin.y == end.y) //����Ϊͬһ��;
    {
        return false;
    }
    for (int i = temp1 - 1; i >= 0; i--) //�жϷ����������Ϸ�������ˮƽ��ȥ�Ŀ���;
    {
        begin.x = i;
        if (isBlocked(i, begin.y))
            break;
        if (horizon(begin, end))
            return 1;
    }
    for (int i = temp1 + 1; i <= 15; i++) //�жϷ����������·���������ˮƽ��ȥ����;
    {
        begin.x = i;
        if (isBlocked(i, begin.y))
            break;
        if (horizon(begin, end))
            return 1;
    }
    begin.x = temp1;
    for (int i = temp2 - 1; i >= 0; i--) //�жϷ��������������������ȥ����;
    {
        begin.y = i;
        if (isBlocked(begin.x, i))
            break;
        if (vertical(begin, end))
            return 1;
    }
    for (int i = temp2 + 1; i <= 13; i++) //�жϷ������������������ȥ����;
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
	if (begin.x == end.x && begin.y == end.y) //����Ϊͬһ��;
        return 0;
    for (int i = temp1 - 1; i >= 0; i--) //ͬturn_once��ע�ģ��ж��Ƿ���ܾ���һ��ת����ȥ;
    {
        begin.x = i;
        if (isBlocked(i, begin.y))
            break;
        if (turn_once(begin, end))
            return 1;
    }
    for (int i = temp1 + 1; i <= 15; i++) //����ѭ����ͬ��;
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
int judge() //�ж��Ƿ���10������
{
    int num = 0;
    for (int i = 1; i <= 14; i++) //�������飬Ѱ�����ڵ�;
        for (int j = 1; j <= 12; j++)
        {
            if (map[i][j] != -1 && (map[i - 1][j] == map[i][j] || map[i + 1][j] == map[i][j] || map[i][j - 1] == map[i][j] || map[i][j + 1] == map[i][j]))
                num++;
        }
    if (num < 10) //��С��10�������ţ�ֱ������ֵΪ1Ϊֹ;
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
    while (i < 100) //�����ܴ���,ѭ��1000��;
    {
        for (int i = 1; i <= 14; i++)
            for (int j = 1; j <= 10; j++)
            {
                int temp1 = map[i][j];
                int col = rand() % 10 + 1;
                int row = rand() % 14 + 1;
                if (!flag) //Ϊ���������ţ��������������ݵ�����;
                {
                    if (temp1 == -1)
                        continue;
                    if (map[row][col] == -1 || map[i][j] == -1)
                        continue;
                    else
                    {
                        map[i][j] = map[row][col]; //�������鶼�������;
                        map[row][col] = temp1;
                    }
                }
                else //��Ϸ�е�����;
                {
                    if (map[i][j] != -1 && map[row][col] != -1)
                    {
                        map[i][j] = map[row][col]; //�������鶼�������;
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
        if (!flag1) //����������;
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
                if (!flagmusic) //�ж��Ƿ������;
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