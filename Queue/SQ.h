#ifndef SQ_H_INCLUDED
#define SQ_H_INCLUDED

#include <iostream>
#include <utility>
#include <initializer_list>

namespace sq{
    using namespace std;


    template<typename> class Queue;
    template<typename T>
        void printQueue(const Queue<T>&);

    template<class DataType>
    class Queue
    {
    public:
        //default construct
        Queue(int m=10);

        //initializer list construct
        Queue(initializer_list<DataType> Q);

        //Big Five
        ~Queue();

        Queue(const Queue &rhs);

        Queue& operator=(const Queue &rhs);

        Queue(Queue&& rhs);

        Queue& operator=(Queue&& rhs);

        void swap(Queue& rhs);

    public:
        void EnQueue(const DataType& x);

        void EnQueue(DataType&& x);

        void DeQueue();

        const DataType& top()const
        {
            return data[front];
        }

        DataType& top()
        {
            return data[front];
        }

        const DataType& back()const
        {
            return data[rear-1];
        }

        DataType& back()
        {
            return data[rear-1];
        }

        bool full()const
        {
            return theSize==maxSize;
        }

        bool empty()const
        {
            return theSize==0;
        }

        int Size()const
        {
            return theSize;
        }

        friend void printQueue<DataType>(const Queue<DataType>&);

    private:
        int front;
        int rear;
        int maxSize;
        int theSize;
        DataType* data;

        void init(int m);
    };
}
#endif // SQ_H_INCLUDED
