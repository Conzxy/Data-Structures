#ifndef LQ_H_INCLUDED
#define LQ_H_INCLUDED

#include <iostream>
#include <utility>
#include <initializer_list>

namespace lq{
    using namespace std;

    template<typename DataType>
    class LQueue
    {
    private:
        struct Node;
    public:
        class const_iterator;
        class iterator;
    public:
        //default construct
        LQueue();

        //initializer-list constructor
        LQueue(initializer_list<DataType>& Q);

        //Big Five
        ~LQueue();

        LQueue(const LQueue& rhs);

        LQueue& operator=(const LQueue& rhs);

        LQueue(LQueue&& rhs);

        LQueue& operator=(LQueue&& rhs);

        void swap(LQueue& rhs);

    public:
        const_iterator begin()const
        {
            return {front->next};
        }

        iterator begin()
        {
            return {front->next};
        }

        const_iterator end()const
        {
            return {rear->next};
        }

        iterator end()
        {
            return {rear->next};
        }

        int Size()const
        {
            return theSize;
        }

        bool empty()const
        {
            return theSize==0;
        }
        void push(const DataType& x)
        {
            EnQueue(x);
        }

        void push(DataType&& x)
        {
            EnQueue(move(x));
        }
        void pop()
        {
            if(!empty())
                DeQueue();
        }

        DataType& top()
        {
            return *begin();
        }

        const DataType& top()const
        {
            return *begin();
        }

        void EnQueue(const DataType& x);

        void EnQueue(DataType&& x);

        iterator DeQueue();

        void clear()
        {
            while(!empty())
                pop();
        }

    private:
        int theSize;
        Node* front;
        Node* rear;

        void init();         //routine initializer operation
    };
}

void solve2();
#endif // LQ_H_INCLUDED
