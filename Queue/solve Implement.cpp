#include "SQ.h"
#include "LQ.h"
#include <string>
using namespace std;

void solve1()
{
    int len,x;
    string str;
    cin>>len;
    Queue<int> Q(len);

    while(cin>>str&&str!="end")
    {
        if(str=="in")
        {   cin>>x;
            Q.EnQueue(x);
        }
        else if(str=="out")
            Q.DeQueue();
    }
    printQueue(Q);
}

void solve2()
{
    LQueue<int> Q;
    string str;
    int x;
    while(cin>>str&&str!="end")
    {
        if(str=="in")
        {
            cin>>x;
            Q.push(x);
        }
        else if(str=="out")
            Q.pop();
    }
    printLQueue(Q);
}
