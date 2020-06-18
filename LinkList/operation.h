#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#include "LinkList.h"
#include "iterator.h"

namespace LL
{

    template<typename T>
    void List<T>::init()
    {
        theSize=0;
        head=new Node;
        tail=new Node;
        head->next=tail;
        tail->prev=head;
    }

    template<typename T>
    List<T>::List(initializer_list<T> L)            //list initialization constructor
    {
        init();
        for(auto &c:L)
            push_back(c);
    }

    //Big Five
    template<typename T>
    List<T>::~List()                                     //deconstructor
    {
        clear();
        delete head;
        delete tail;
    }

    template<typename T>
    List<T>::List(const List& rhs)                       //copy constructor
    {
        init();
        for(auto &x:rhs)
        {
            push_back(x);
        }
    }

    template<typename T>
    List<T>& List<T>::operator=(const List &rhs)         //overloading copy-assignment operator
    {
        using std::swap;                                 //allow ADL

        auto copy=rhs;
        swap(*this,copy);
        return *this;
    }

    template<typename T>
    List<T>::List(List&& rhs):theSize{rhs.theSize},head{rhs.head},tail{rhs.tail} //move constructor
    {
        rhs.theSize=0;
        rhs.head=nullptr;
        rhs.tail=nullptr;
    }


    template<typename T>
    List<T>& List<T>::operator=(List&& rhs)                     //overloading move-assignment operator
    {
        using std::swap;
        swap(*this,rhs);
        return *this;
    }

    template<typename T>
    void List<T>::swap(List<T>& rhs)                            //member vesion
    {
        using std::swap;
        swap(theSize,rhs.theSize);
        swap(head,rhs.head);
        swap(tail,rhs.tail);
    }

    template<typename T>
    void swap(List<T>& lhs,List<T>& rhs)                        //non-member version
    {
        lhs.swap(rhs);
    }

    //gets the iterator at position address
    template<typename T>
    typename List<T>::iterator List<T>::find(iterator itr,int address)
    {
        for(int i=1;i<address;i++)
            itr++;
        return itr;
    }

    //Insert x before itr
    template<typename T>
    typename List<T>::iterator List<T>::insert(iterator itr,const T&x)
    {
        Node *p=itr.current;
        theSize++;
        return {p->prev=p->prev->next=new Node{x,p->prev,p}};
    }

    template<typename T>
    typename List<T>::iterator List<T>::insert(List<T>::iterator itr,T &&x)
    {
        Node *p=itr.current;
        theSize++;
        return {p->prev=p->prev->next=new Node{x,p->prev,p}};
    }

    //Erase item at iter
    template<typename T>
    typename List<T>::iterator List<T>::erase(iterator itr)
    {
        Node *p=itr.current;
        iterator retval{p->next};
        p->prev->next=p->next;
        p->next->prev=p->prev;
        delete p;
        theSize--;
        return retval;
    }

    template<typename T>
    typename List<T>::iterator List<T>::erase(iterator from,iterator to)
    {
        for(iterator itr=from;itr!=to;)
            itr=erase(itr);

        return to;
    }

    template<typename T>
    void solve1(List<T> &L);

    template<typename T>
    void solve2(List<T> &L);

    template<typename T>
    void solve3(List<T> &L);

    template<typename T>
    void solve4(List<T> &L);

    template<typename T>
    void solve5(List<T> &L);

    template<typename T>
    void solve6(List<T> &L);

    template<typename T>
    void solve7(List<T> &L);
}

#endif // OPERATION_H_INCLUDED
