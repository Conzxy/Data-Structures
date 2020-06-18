#ifndef ITERATOR_H_INCLUDED
#define ITERATOR_H_INCLUDED

#include "LinkList.h"

namespace LL {

    template<typename Object>
    struct List<Object>::Node
    {
        Object data;            //结点数据
        Node* prev;             //前驱
        Node* next;             //后驱

        //construct
        Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr) :     //default and accept lvalue
            data(d), prev(p), next(n) {}
        Node(Object&& d, Node* p = nullptr, Node* n = nullptr) :                  //accept rvalue
            data(std::move(d)), prev(p), next(n) {}
    };

    template<typename Object>
    class List<Object>::const_iterator        //nested class
    {
    public:
        const_iterator() :current{ nullptr } {} //default constructor

        const Object& operator*()const      //overloading dereference operator
        {
            return retrieve();
        }

        const_iterator& operator++();        //overloading Preincrement operator

        const_iterator operator++(int);      //overloading Postincrement operator

        const_iterator& operator--();        //overloading Predecrement operator

        const_iterator operator--(int);      //overloading Postdecrement operator

        bool operator==(const const_iterator& rhs)const //overloading ==
        {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator& rhs)const //overloading !=
        {
            return !(*this == rhs);
        }

        const_iterator prev()const               //get prev
        {
            return { current->prev };
        }

        const_iterator next()const               //get next
        {
            return { current->next };
        }

        const Node* NodeAddress()const           //get Node pointer
        {
            return address();
        }
    protected:
        Node* current;                           //data member
        Object& retrieve()const                  //interface of dereference operation
        {
            return current->data;
        }

        Node* address()const                     //interface of NodeAddress()
        {
            return current;
        }

        const_iterator(Node* p) :current{ p } {}     //constructor

        friend class List<Object>;               //friend declaration
    };

    template<typename Object>
    class List<Object>::iterator :public const_iterator   //inherited from const_iterator
    {
    public:
        iterator() {}                             //default constructor

        Object& operator*()
        {
            return const_iterator::retrieve();
        }

        const Object& operator*()const
        {
            return const_iterator::retrieve();
        }

        iterator& operator++();

        iterator operator++(int);

        iterator& operator--();

        iterator operator--(int);

        iterator prev()const
        {
            return { this->current->prev };
        }

        iterator next()const
        {
            return { this->current->next };
        }

        Node* NodeAddress()
        {
            return const_iterator::address();
        }

    protected:
        iterator(Node* p) :const_iterator{ p } {}       //use const_iterator's constructor to initiallizer data member
                                                    //from const_iterator class
        friend class List<Object>;
    };

    //const_iterator
    template<typename T>
    typename List<T>::const_iterator& List<T>::const_iterator::operator++()        //overloading Preincrement operator
    {
        current = current->next;
        return *this;
    }

    template<typename T>
    typename List<T>::const_iterator List<T>::const_iterator::operator++(int)      //overloading Postincrement operator
    {
        const_iterator old = *this;
        ++(*this);
        return old;
    }

    template<typename T>
    typename List<T>::const_iterator& List<T>::const_iterator::operator--()        //overloading Predecrement operator
    {
        current = current->prev;
        return *this;
    }

    template<typename T>
    typename List<T>::const_iterator List<T>::const_iterator::operator--(int)      //overloading Postdecrement operator
    {
        const_iterator old = *this;       //尽管进行的是浅拷贝，但const_iterator并未设置析构，因此堆内存都不会得到释放
        --(*this);                      //old与*this一开始指向同一内存空间，后*this前移，而old（浅）拷贝一份返回，
        return old;                     //原来的old在离开作用域时被销毁
    }

    //iterator
    template<typename T>
    typename List<T>::iterator& List<T>::iterator::operator++()
    {
        this->current = this->current->next;
        return *this;
    }

    template<typename T>
    typename List<T>::iterator List<T>::iterator::operator++(int)
    {
        iterator old = *this;
        ++(*this);
        return old;
    }

    template<typename T>
    typename List<T>::iterator& List<T>::iterator::operator--()
    {
        this->current = this->current->prev;
        return *this;
    }

    template<typename T>
    typename List<T>::iterator List<T>::iterator::operator--(int)
    {
        iterator old = *this;
        --(*this);
        return old;
    }
}


#endif // ITERATOR_H_INCLUDED
