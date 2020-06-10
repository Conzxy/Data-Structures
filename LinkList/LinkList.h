#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

#include <iostream>
#include <utility>
#include <initializer_list>

template<typename> class List;
template<typename T>
    typename List<T>::Node* solve2(List<T>&); //Forward declaration

template<typename Object>
class List
{
private:
    struct Node
    {
        Object data;
        Node* prev;
        Node* next;

        Node(const Object &d=Object{},Node *p=nullptr,Node *n=nullptr):
            data(d),prev(p),next(n){}
        Node (const Object &&d,Node *p=nullptr,Node *n=nullptr):
            data(std::move(d)),prev(p),next(n){}
    };

public:
    class const_iterator        //nested class
    {
    public:
        const_iterator():current{nullptr}{}

        const Object &operator*()const      //dereference
        {return retrieve();}

        const_iterator& operator++()        //Preincrement
        {
            current=current->next;
            return *this;
        }

        const_iterator operator++(int)      //Postincrement
        {
            const_iterator old=*this;
            ++(*this);
            return old;
        }

        const_iterator& operator--()        //Predecrement
        {
            current=current->prev;
            return *this;
        }

        const_iterator operator--(int)      //Postdecrement
        {
            const_iterator old=*this;       //尽管进行的是浅拷贝，但const_iterator并未设置析构，因此堆内存都不会得到释放
            --(*this);                      //old与*this一开始指向同一内存空间，后*this前移，而old（浅）拷贝一份返回，
            return old;                     //原来的old在离开作用域时被销毁
        }

        bool operator==(const const_iterator& rhs)const
        {return current==rhs.current;}

        bool operator!=(const const_iterator& rhs)const
        {return !(*this==rhs);}

        const_iterator prev()const               //前驱
        {return {current->prev};}

        const_iterator next()const               //后驱
        {return {current->next};}

        const Node* NodeAddress()const           //节点指针
        {return address();}
    protected:
        Node *current;
        Object& retrieve()const
        {return current->data;}

        Node* address()const
        { return current;}

        const_iterator(Node *p):current{p}{}

        friend class List<Object>;
    };

    class iterator :public const_iterator
    {
    public:
        iterator(){}

        Object& operator*()
        { return const_iterator::retrieve();}

        const Object& operator*()const
        { return const_iterator::retrieve();}

        iterator& operator++()
        {
            this->current=this->current->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator old=*this;
            ++(*this);
            return old;
        }

        iterator& operator--()
        {
            this->current=this->current->prev;
            return *this;
        }

        iterator operator--(int)
        {
            iterator old=*this;
            --(*this);
            return old;
        }

        iterator prev()const
        {return {this->current->prev};}

        iterator next()const
        {return {this->current->next};}

        Node* NodeAddress()
        {return const_iterator::address();}

    protected:
        iterator(Node *p):const_iterator{p}{}

        friend class List<Object>;
    };
public:

    List()
    { init();}
    List(std::initializer_list<Object> l)       //列表初始化
    {
        init();
        for(auto &c:l)
            push_back(c);
    }
    //Big Five
    ~List()
    {
        clear();
        delete head;
        delete tail;
    }

    List(const List& rhs)
    {
        init();
        for(auto &x:rhs)
        {
            push_back(x);
        }
    }

    List& operator=(const List &rhs)
    {
        List copy=rhs;
        std::swap(*this,copy);
        return *this;
    }

    List(List&& rhs):theSize{rhs.theSize},head{rhs.head},tail{rhs.tail}
    {
        rhs.theSize=0;
        rhs.head=nullptr;
        rhs.tail=nullptr;
    }

    List& operator=(List&& rhs)
    {
        std::swap(theSize,rhs.theSize);
        std::swap(head,rhs.head);
        std::swap(tail,rhs.tail);

        return *this;
    }

    iterator begin()
    { return {head->next};}

    const_iterator begin()const
    { return {head->next};}

    iterator end()
    { return {tail};}

    const_iterator  end()const
    { return {tail};}

    int Size()const
    { return theSize;}

    bool empty()const
    { return theSize==0;}

    void clear()
    {
        while(!empty())
            pop_front();
    }

    Object& front()
    { return *begin();}

    const Object& front()const
    { return *begin();}

    Object& back()
    { return *--end();}

    const Object& back()const
    { return *--end();}

    void push_front(const Object& x)
    { insert(begin(),x);}

    void push_front(Object&& x)
    { insert(begin(),std::move(x));}

    void push_back(const Object& x)
    { insert(end(),x);}

    void push_back(Object &&x)
    { insert(end(),std::move(x));}

    void pop_front()
    { erase(begin());}

    void pop_back()
    { erase(--end());}

    iterator find(iterator itr,int address)
    {
        for(int i=1;i<address;i++)
            itr++;
        return itr;
    }

    //Insert x before itr
    iterator insert(iterator itr,const Object &x)
    {
        Node *p=itr.current;
        theSize++;
        return {p->prev=p->prev->next=new Node{x,p->prev,p}};
    }

    iterator insert(iterator itr,Object &&x)
    {
        Node *p=itr.current;
        theSize++;
        return {p->prev=p->prev->next=new Node{x,p->prev,p}};
    }

    //Erase item at iter
    iterator erase(iterator itr)
    {
        Node *p=itr.current;
        iterator retval{p->next};
        p->prev->next=p->next;
        p->next->prev=p->prev;
        delete p;

        return retval;
    }

    iterator erase(iterator from,iterator to)
    {
        for(iterator itr=from;itr!=to;)
            itr=erase(itr);

        return to;
    }

public:

    //template<typename T>
    //friend typename List<T>::Node* solve2(List<T> &L);

    friend List<Object>::Node* solve2<Object>(List<Object>& L);

private:
    int theSize;
    Node *head;
    Node *tail;

    void init()
    {
        theSize=0;
        head=new Node;
        tail=new Node;
        head->next=tail;
        tail->prev=head;
    }

};


template<typename T>
void printList_front(const List<T>& L)
{
    for(auto &x:L)
        std::cout<<" "<<x;
    std::cout<<std::endl;
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
List<T> reverse_List(const List<T>& L)          //倒置链表
{
    List<T> La;
    for(auto itr=L.end().prev();itr!=L.begin().prev();itr--)
        La.push_back(*itr);
    return La;
}

void solve1(List<int> &L);

//template<typename T>
//typename List<T>::Node* solve2(List<T>& L)
template<typename Object>
typename List<Object>::Node* solve2(List<Object>& L)        //需要前置声明
{
        int n,k,x;
        std::cin>>n>>k;
        for(int i=0;i<n;i++)
        {
            std::cin>>x;
            L.push_back(x);
        }
        auto itr=L.begin();
        for(int i=1;i<k;i++)
            itr++;
        return itr.NodeAddress();
}

void solve3(List<int> &L);

void solve4(List<int> &L);

void solve5(List<int> &L);

void solve6(List<int> &L);

void solve7(List<int> &L);
#endif // LINKLIST_H_INCLUDED
