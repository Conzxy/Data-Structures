#ifndef SOLVE_H_INCLUDED
#define SOLVE_H_INCLUDED

#include "LinkList.h"
#include "operation.h"
#include "iterator.h"

namespace LL{
    template<typename T>
    void solve1(List<T>& L)   //倒置链表
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

        reverse_List(L);
        printList_back(L);
    }

    template<typename Object>
    typename List<Object>::Node* getPtr(List<Object>& L, int k)
    {
        if (k > L.Size() || k == 0) return nullptr;
        auto itr = L.find(L.begin(), k);
        return itr.NodeAddress();
    }

    template<typename T>
    void solve2(List<T>& L)
    {
        int n, x, k;
        cin >> n>>k;
        for (int i = 0; i < n; i++)
        {
            cin >> x;
            L.push_back(x);
        }
        cout<<((getPtr(L,k)==nullptr)?"FALSE":"TRUE");
    }

    template<typename T>
    void solve3(List<T> &L)   //在第i个节点插入值为x的结点
    {
        int n,x,k,j;    //n:结点数；x:结点数据；k：结点位置，j：插入值
        cin>>n>>k>>j;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            L.push_back(x);
        }

        if(k<=L.Size()&&k>0)
        {
            auto itr=L.find(L.begin(),k);
            L.insert(itr,j);
        }
        printList_back(L);
    }

    template<typename T>
    void solve4(List<T>& L)       //删除第i个结点
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
            auto itr=L.find(L.begin(),k);
            L.erase(itr);
        }

        printList_back(L);
    }

    template<typename T>
    void solve5(List<T>& L)       //在有序链表中插入为x的结点
    {
        int n,x,k;//n：结点数，x：结点数据，k：插入值
        cin>>n>>k;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            L.push_back(x);
        }
        if(L.Size()==0||k>=L.back())
                L.push_back(k);
        else
            for(auto itr=L.begin();itr!=L.end();itr++)
                if(*itr.prev()<=k&&*itr>=k)
                    {L.insert(itr,k);break;}
        printList_back(L);
    }

    template<typename T>
    void solve6(List<T> &L)       //奇数项和偶数项结点分离
    {
        int n,x,cnt;//n:结点数，x结点数据，cnt：奇偶结点计数
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cin>>x;
            L.push_back(x);
        }
        List<T> Ln;
        vector<T> vec;

        cnt=0;
        for(auto &x:L)
        {
            cnt++;
            if(cnt%2!=0)
            {
                vec.push_back(x);
            }
        }

        cnt=0;
        for(auto &x:L)
        {
            cnt++;
            if(cnt%2==0)
            {
                vec.push_back(x);
            }
        }

        for(int i=0;i<n;i++)
        {
            Ln.push_back(vec[i]);
        }

        printList_back(Ln);
    }

    template<typename T>
    void solve7(List<T>& L)       //有序链表的交集
    {
        List<T> L1,L2;
        T x;
        int n1,n2;
        cin>>n1;
        for(int i=0;i<n1;i++)
        {
            cin>>x;
            L1.push_back(x);
        }
        cin>>n2;
        for(int i=0;i<n2;i++)
        {
            cin>>x;
            L2.push_back(x);
        }
        for(auto &x:L1)
            for(auto &y:L2)
                if(x==y)
                    L.push_back(x);
        printList_back(L);
    }

    template<typename T>
    void printList_front(const List<T>& L)
    {
        for(auto &x:L)
            cout<<" "<<x;
        cout<<endl;
    }

    template<typename T>
    void printList_back(const List<T>& L)
    {
        for(auto itr=L.begin();itr!=L.end();itr++)
        {
            if(itr==--L.end())
                std::cout<<*itr;
            else
                std::cout<<*itr<<" ";
        }
        std::cout<<std::endl;
    }

    template<typename T>
    void reverse_printList(const List<T>& L)        //倒置输出链表
    {
        for(auto itr=L.end().prev();itr!=L.begin().prev();itr--)
            std::cout<<" "<<*itr;
        std::cout<<std::endl;
    }

    template<typename T>
    void reverse_List(List<T> &L)
    {
        int len=L.Size();
        auto it=L.begin();
        for(int i=0;i<len-1;i++)
        {
            L.insert(it,L.back());
            L.pop_back();
        }
    }

}

#endif // SOLVE_H_INCLUDED
