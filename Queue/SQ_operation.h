#ifndef SQ_OPERATION_H_INCLUDED
#define SQ_OPERATION_H_INCLUDED

#include "SQ.h"

namespace sq
{
    template<typename T>
    Queue<T>::Queue(int m)
    {
        init(m);
    }

    template<typename DataType>
    Queue<DataType>::Queue(initializer_list<DataType> Q)
    {
        init(30);
        for(auto &x:Q)
        {
            EnQueue(x);
        }
    }

    template<typename T>
    Queue<T>::~Queue(){delete[]data;}

    template<typename DataType>
    Queue<DataType>::Queue(const Queue &rhs):front(rhs.front),rear(rhs.rear),maxSize(rhs.maxSize),theSize(rhs.theSize),data{new DataType[maxSize]}
    {
        for(int i=0;i!=theSize;i++)
            *(data+i)=*(rhs.data+i);
            //data[i]=rhs.data[i];
    }

    template<typename T>
    Queue<T>& Queue<T>::operator=(const Queue &rhs)
    {
        using std::swap;

        Queue copy=rhs;
        swap(*this,copy);
        return *this;
    }

    template<typename T>
    Queue<T>::Queue(Queue&& rhs):front(rhs.front),rear(rhs.rear),maxSize(rhs.maxSize),theSize(rhs.theSize),data(rhs.data)
    {
        rhs.front=rhs.rear=rhs.maxSize=rhs.theSize=0;
        rhs.data=nullptr;
    }

    template<typename T>
    Queue<T>& Queue<T>::operator=(Queue&& rhs)
    {
        using std::swap;
        swap(*this,rhs);
        return *this;
    }

    template<typename T>
    void Queue<T>::swap(Queue& rhs)
    {
        using std::swap;
        swap(front,rhs.front);
        swap(rear,rhs.rear);
        swap(maxSize,rhs.maxSize);
        swap(theSize,rhs.theSize);
        swap(data,rhs.data);
    }

    template<typename DataType>
    void Queue<DataType>::EnQueue(const DataType& x)
    {
        if(full())
            return ;
        data[rear]=x;                   //rear赋新值
        rear=(rear+1)%maxSize;          //rear后移
        theSize++;
    }

    template<typename DataType>
    void Queue<DataType>::EnQueue(DataType&& x)
    {
        if(full())
            return ;
        data[rear]=x;
        rear=(rear+1)%maxSize;
        theSize++;
    }

    template<typename T>
    void Queue<T>::DeQueue()
    {
        if(empty())
            return ;
        front=(front+1)%maxSize;        //front后移，成为新的队首
        theSize--;
    }

    template<typename DataType>
    void Queue<DataType>::init(int m)
    {
        front=0;
        rear=0;
        maxSize=m;
        theSize=0;
        data=new DataType[maxSize];
    }

    template<typename T>
    void printQueue(const Queue<T>& Q)
    {
        if(Q.empty())
            return ;
        cout<<"Queue length: "<<Q.Size()<<endl;
        cout<<"Queue data: ";
        cout << Q.data[Q.front] << " ";
        for(int p=Q.front+1;p!=Q.rear;p=(p+1)%Q.maxSize)
        {
            cout<<Q.data[p]<<" ";
        }
    }

    template<typename T>
    void swap(Queue<T> &lhs,Queue<T> &rhs)
    {
        lhs.swap(rhs);
    }

}
void solve1();
#endif // SQ_OPERATION_H_INCLUDED
