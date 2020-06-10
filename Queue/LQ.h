#ifndef LQ_H_INCLUDED
#define LQ_H_INCLUDED

#include <iostream>
#include <utility>
#include <initializer_list>

template<typename> class LQueue;
template<typename T>
    void swap(LQueue<T>&,LQueue<T>&);
//template<typename T>
    //void printLQueue(const LQueue<T>&);
template<typename DataType>
class LQueue
{
private:
    struct Node
    {
        DataType data;  //结点数据
        Node* next;     //下一个结点

        Node(const DataType &d=DataType{},Node* n=nullptr):data{d},next{n}{}    //lvalue
        Node(DataType &&d,Node* n=nullptr):data{std::move(d)},next{n}{}         //rvalue
    };
public:
    class const_iterator;
    class iterator;
public:
    //default construct
    LQueue()
    {
        init();
    }

    //initializer-list constructor
    LQueue(std::initializer_list<DataType> Q)
    {
        init();
        for(auto &x:Q)
            push(x);
    }
    //Big Five
    ~LQueue()
    {
        clear();
        delete front;
        delete rear;
    }
    LQueue(const LQueue& rhs)
    {
        init();
        for(auto &x:rhs)
            push(x);
    }

    LQueue& operator=(const LQueue& rhs)
    {
        auto copy=rhs;
        swap(*this,copy);
        return *this;
    }

    LQueue(LQueue&& rhs):theSize{rhs.theSize},front{rhs.front},rear{rhs.rear}
    {
        rhs.theSize=0;
        rhs.front=nullptr;
        rhs.rear=nullptr;
    }

    LQueue& operator=(LQueue&& rhs)
    {
        swap(*this,rhs);
        return *this;
    }
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
        EnQueue(std::move(x));
    }
    void pop()
    {
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

    void EnQueue(const DataType& x)
    {
        rear->next=new Node{x,nullptr};
        rear=rear->next;
        theSize++;
    }

    void EnQueue(DataType&& x)
    {
        rear->next=new Node{x,nullptr};
        rear=rear->next;
        theSize++;
    }

    void DeQueue()
    {
        Node *p=front->next;
        front->next=p->next;
        if(theSize==1)
            rear=front;
        theSize--;
        delete p;
    }

    void clear()
    {
        while(!empty())
            pop();
    }

public:
    friend void swap<DataType>(LQueue<DataType>&,LQueue<DataType>&);
    //friend void printLQueue<DataType>(const LQueue<DataType>&);
private:
    int theSize;
    Node* front;
    Node* rear;

    void init()         //routine initializer operation
    {
        theSize=0;
        front=new Node;
        rear=new Node;
        front=rear;
    }
};

template<typename T>
void swap(LQueue<T>& lhs,LQueue<T>& rhs)
{
    using std::swap;
    swap(lhs.theSize,rhs.theSize);
    swap(lhs.front,rhs.front);
    swap(lhs.rear,rhs.rear);
}
template<typename T>
class LQueue<T>::const_iterator
{
public:
    const_iterator():current{nullptr}{}

    const T& operator*()const
    {
        return retrieve();
    }

    const_iterator& operator++()
    {
        current=current->next;
        return *this;
    }

    const_iterator operator++(int)
    {
        auto old=*this;
        ++(*this);
        return old;
    }

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

    iterator& operator++()
    {
        this->current=this->current->next;
        return *this;
    }

    iterator operator++(int)
    {
        auto old=*this;
        ++(*this);
        return old;
    }
protected:
    iterator(Node* p):const_iterator{p}{}

    friend class LQueue<T>;
};

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

void solve2();
#endif // LQ_H_INCLUDED
