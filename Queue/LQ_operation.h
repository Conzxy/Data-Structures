#ifndef LQ_OPERATION_H_INCLUDED
#define LQ_OPERATION_H_INCLUDED

#include "LQ.h"

namespace lq{
    //template<typename T>
    //using citr=typename LQueue<T>::const_iterator;
    //why citr<T>& LQueue<T>::const_iterator::operator++() is error?

    template<typename DataType>
    struct LQueue<DataType>::Node
    {
        DataType data;  //结点数据
        Node* next;     //下一个结点

        Node(const DataType &d=DataType{},Node* n=nullptr):data{d},next{n}{}    //lvalue
        Node(DataType &&d,Node* n=nullptr):data{std::move(d)},next{n}{}         //rvalue
    };

    template<typename T>
    class LQueue<T>::const_iterator
    {
    public:
        const_iterator():current{nullptr}{}

        const T& operator*()const
        {
            return retrieve();
        }

        const_iterator& operator++();

        const_iterator operator++(int);

        bool operator==(const const_iterator& rhs)
        {
            return current==rhs.current;
        }

        bool operator!=(const const_iterator& rhs)
        {
            return !(*this==rhs);
        }
    protected:
        Node* current;
        const_iterator(Node *p):current{p}{}

        T& retrieve()const
        {
            return current->data;
        }

        friend class LQueue<T>;
    };

    template<typename T>
    class LQueue<T>::iterator :public const_iterator
    {
        iterator(){}

        T& operator*()
        {
            return const_iterator::retrieve();
        }

        const T& operator*()const
        {
            return const_iterator::retrieve();
        }

        iterator& operator++();

        iterator operator++(int);

    protected:
        iterator(Node* p):const_iterator{p}{}

        friend class LQueue<T>;
    };



    //const_iterator
    template<typename T>
    typename LQueue<T>::const_iterator& LQueue<T>::const_iterator::operator++()
    {
        current=current->next;
        return *this;
    }

    template<typename T>
    typename LQueue<T>::const_iterator LQueue<T>::const_iterator::operator++(int)
    {
        auto old=*this;
        ++(*this);
        return old;
    }

    //iterator
    template<typename T>
    typename LQueue<T>::iterator& LQueue<T>::iterator::operator++()
    {
        this->current=this->current->next;
        return *this;
    }

    template<typename T>
    typename LQueue<T>::iterator LQueue<T>::iterator::operator++(int)
    {
        auto old=*this;
        ++(*this);
        return old;
    }

    //LQueue
    template<typename T>
    LQueue<T>::LQueue()
    {
        init();
    }

    template<typename DataType>
    LQueue<DataType>::LQueue(initializer_list<DataType>& Q)
    {
        init();
        for(auto &x:Q)
            push(x);
    }

    template<typename T>
    LQueue<T>::~LQueue()
    {
        clear();
        delete front;
        delete rear;
    }

    template<typename T>
    LQueue<T>::LQueue(const LQueue& rhs)
    {
        init();
        for(auto &x:rhs)
            push(x);
    }

    template<typename T>
    LQueue<T>& LQueue<T>::operator=(const LQueue& rhs)
    {
        using std::swap;

        auto copy=rhs;
        swap(*this,copy);
        return *this;
    }

    template<typename T>
    LQueue<T>::LQueue(LQueue&& rhs):theSize{rhs.theSize},front{rhs.front},rear{rhs.rear}
    {
        rhs.theSize=0;
        rhs.front=nullptr;
        rhs.rear=nullptr;
    }

    template<typename T>
    LQueue<T>& LQueue<T>::operator=(LQueue&& rhs)
    {
        using std::swap;
        swap(*this,rhs);
        return *this;
    }

    template<typename T>
    void LQueue<T>::swap(LQueue& rhs)
    {
        using std::swap;
        swap(theSize,rhs.theSize);
        swap(front,rhs.front);
        swap(rear,rhs.rear);
    }

    template<typename T>
    void swap(LQueue<T>& lhs,LQueue<T>& rhs)
    {
        lhs.swap(rhs);
    }

    template<typename DataType>
    void LQueue<DataType>::EnQueue(const DataType& x)
    {
        rear->next= new Node{x,nullptr};
        rear=rear->next;
        theSize++;
    }

    template<typename DataType>
    void LQueue<DataType>::EnQueue(DataType&& x)
    {
        rear->next=new Node{x,nullptr};     //新结点接在尾指针之后
        rear=rear->next;                    //尾指针指向新结点
        theSize++;
    }

    template<typename T>
    typename LQueue<T>::iterator LQueue<T>::DeQueue()
    {
        Node *p=front->next;            //记录队首
        iterator retval{p->next};
        if(theSize==1)
            rear=front;                 //若只有队首则置为空表状态
        else
        {
            front->next=p->next;        //队首更新为队首的下一位
        }

        theSize--;
        delete p;
        return retval;
    }

    template<typename T>
    void LQueue<T>::init()
    {
        theSize=0;
        front=new Node;
        rear=new Node;
        front=rear;
    }

    template<typename T>
    void printLQueue(const LQueue<T>& Q)
    {
        if(Q.empty())
            return ;
        std::cout<<"Queue length: "<<Q.Size()<<std::endl;
        std::cout<<"Queue data: ";
        for(auto &x:Q)
            std::cout<<" "<<x;
    }
}
#endif // LQ_OPERATION_H_INCLUDED
