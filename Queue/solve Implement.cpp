#include "SQ.h"

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
