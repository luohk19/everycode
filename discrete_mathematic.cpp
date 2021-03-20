#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;
class lesson
{
public:
    int time;
    int before;
    int num;
    bool flag;
    int *biggest; //change
    int *next;
    lesson()
    {
        time = 0;
        flag = false;
        num = 0;
        biggest = nullptr;
    }
    ~lesson()
    {
        delete[] next;
        delete[] biggest;
    }
};
int *maxtime;
void search_maxtime(lesson *course, int i)
{
    if (course[i].before == 0)
    { //如果是起点
        maxtime[i] = course[i].time;
        // course[i].biggest = ;
        course[i].biggest = nullptr;
        return;
    }
    int max = 0;
    int num = 0;
    int key = -1;
    for (int j = 0; j < course[i].before; j++)
    {
        if (maxtime[course[i].next[j] - 1] == -1)
        {
            search_maxtime(course, course[i].next[j] - 1);
        }
        int temp = maxtime[course[i].next[j] - 1];
        if (temp > max)
        {
            max = temp;
            key = course[i].next[j] - 1;
        }
    }
    for (int j = 0; j < course[i].before; j++)
    {
        int temp = maxtime[course[i].next[j] - 1];
        if (temp == max)
        {
            course[i].biggest[num++] = course[i].next[j] - 1;
        }
    }
    course[i].num = num;
    maxtime[i] = max + course[i].time;
    // course[i].biggest = key;//可能需要更改，因为关键路径不止一条;
}
void store_in_key(lesson *course, int route)
{
    if(course[route].flag == false){
        course[route].flag = true;
        for (int i = 0; i < course[route].num; i++)
        {
            store_in_key(course, course[route].biggest[i]);
        }
    }
    else return ;
}
int main()
{
    int n, before;
    int *key;
    cin >> n;
    maxtime = new int[n + 1];
    key = new int[n * 3];
    memset(maxtime, -1, n * sizeof(int));
    memset(key, -1, n * sizeof(int));
    lesson *course = new lesson[n + 1];
    for (int i = 0; i < n; i++)
    {
        cin >> course[i].time;
        cin >> course[i].before;
        if (course[i].before != 0)
        {
            course[i].next = new int[course[i].before];
            course[i].biggest = new int[course[i].before];
            memset(course[i].biggest, -1, sizeof(int) * course[i].before);
        }
        else
        {
            course[i].next = nullptr;
            course[i].biggest = nullptr;
        }
        for (int j = 0; j < course[i].before; j++)
        {
            cin >> course[i].next[j];
            // course[course[i].next[j]].flag = true;
        }
    }
    for (int i = 0; i < n; i++)
    {
        search_maxtime(course, i);
    }
    int sign = 0;
    int *route = new int[n];
    int num = 0;
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        int temp = maxtime[i];
        if (maxtime[i] > max)
        {
            max = maxtime[i]; //找到最大时间(可能有很多种最大时间)
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (maxtime[i] == max)
        {
            route[num++] = i;
        }
    }

    for (int i = 0; i < num; i++)
    {
        store_in_key(course, route[i]);
    }
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        cout << maxtime[i] << " ";
        if(course[i].flag == true){
            cout<< 1 <<endl;
        }
        else{
            cout<< 0<< endl;
        }
    }
    //采用邻接表的方案;
    return 0;
}