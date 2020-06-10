#include "LinkList.h"
#include <vector>

using namespace std;

void solve1(List<int> &L)   //倒置链表
{
    int x;
    while(cin>>x)
    {
        L.push_back(x);
        if(getchar()=='\n') break;
    }
    cout<<"Created Sllist:";
    printList_front(L);

    cout<<"Length="<<L.Size()<<endl;

    printList_back(L);

    cout<<"Reversed Sllist:";

    //reverse_printList(L);
    auto L1=reverse_List(L);
    printList_back(L1);
}

void solve3(List<int> &L)   //在第i个节点插入值为x的结点
{
    int n,x,k,j;
    cin>>n>>k>>j;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        L.push_back(x);
    }

    if(k<=L.Size()&&k>0)
    {
        List<int>::iterator itr=L.find(L.begin(),k);
        L.insert(itr,j);
    }
    printList_back(L);
}

void solve4(List<int>& L)       //删除第i个结点
{
    int n,x,k;
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        L.push_back(x);
    }

    if(k<=L.Size()&&k>0)
    {
        List<int>::iterator itr=L.find(L.begin(),k);
        L.erase(itr);
    }

    printList_back(L);
}

void solve5(List<int>& L)       //在有序链表中插入为x的结点
{
    int n,x,k;
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        L.push_back(x);
    }
    for(auto itr=L.begin();itr!=L.end();itr++)//const_iterator?
    {
        if(*itr.prev()<=k&&*itr>=k)
            {L.insert(itr,k);break;}
        if(itr==L.end().prev())
            {L.push_back(k);break;}
    }
    if(L.Size()==0)
        L.push_back(k);
    printList_back(L);
}

void solve6(List<int> &L)       //奇数项和偶数项结点分离
{
    int n,x,cnt;
    cin>>n;
    List<int> Lc;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        L.push_back(x);
    }
    vector<int> vec;
    cnt=0;
    for(auto itr=L.begin();itr!=L.end();itr++)
    {
        cnt++;
        if(cnt%2!=0)
        {
            vec.push_back(*itr);
        }
    }
    cnt=0;
    for(auto itr=L.begin();itr!=L.end();itr++)
    {
        cnt++;
        if(cnt%2==0)
        {
            vec.push_back(*itr);
        }
    }
    for(int i=0;i<n;i++)
    {
        Lc.push_back(vec[i]);
    }
    printList_back(Lc);
}

void solve7(List<int>& L)       //有序链表的交集
{
    List<int> L1,L2;
    int x,n1,n2;
    cin>>n1;
    for(int i=0;i<n1;i++)
    {
        cin>>x;
        L.push_back(x);
    }
    cin>>n2;
    for(int i=0;i<n2;i++)
    {
        cin>>x;
        L1.push_back(x);
    }
    for(auto itr=L.begin();itr!=L.end();itr++)
        for(auto it=L1.begin();it!=L1.end();it++)
            if(*itr==*it)
                L2.push_back(*itr);

    printList_back(L2);
}
