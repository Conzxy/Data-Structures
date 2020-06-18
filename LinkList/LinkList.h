#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

#include <iostream>
#include <utility>
#include <initializer_list>
#include <vector>

namespace LL{
    using namespace std;

    template<typename> class List;
    template<typename T>
    typename List<T>::Node* getPtr(List<T>&, int);

    template<typename Object>
    class List
    {
    private:
        struct Node;                 //aggregation struct:Node data

    public:
        class const_iterator;        //nested class
        class iterator;              //inherited from const_iterator
    public:
        List(){init();}                                     //default constructor

        List(initializer_list<Object>);       //list initialization constructor

        //Big Five
        ~List();                                    //deconstructor

        List(const List& rhs);                      //copy constructor

        List& operator=(const List &rhs);           //overloading copy-assignment operator


        List(List&& rhs);                           //move constructor


        List& operator=(List&& rhs);                //overloading move-assignment operator

    public:
        iterator begin()                            //get the begining Node location of LinkList
        { return {head->next};}

        const_iterator begin()const                 //overloading of begin() base in const
        { return {head->next};}

        iterator end()                              //get the ending Node location of LinkList
        { return {tail};}

        const_iterator end()const                  //end() const version
        { return {tail};}

        int Size()const                             //get the length of LinkList
        { return theSize;}

        bool empty()const                           //empty judgement
        { return theSize==0;}

        void clear()                                //clear LinkList
        {
            while(!empty())
                pop_front();
        }

        Object& front()                             //get the begining Node's value
        { return *begin();}

        const Object& front()const
        { return *begin();}

        Object& back()                              //get the last Node's value
        { return *--end();}

        const Object& back()const
        { return *--end();}

        void push_front(const Object& x)            //insert new Node before the begining Node
        { insert(begin(),x);}

        void push_front(Object&& x)
        { insert(begin(),move(x));}

        void push_back(const Object& x)             //insert new Node before the ending Node
        { insert(end(),x);}

        void push_back(Object &&x)
        { insert(end(),move(x));}

        void pop_front()                            //delete the begining Node
        { erase(begin());}

        void pop_back()                             //delete the last Node
        { erase(--end());}

        iterator find(iterator itr,int address);


        //Insert x before itr
        iterator insert(iterator itr,const Object &x);


        iterator insert(iterator itr,Object &&x);

        //Erase item at iter
        iterator erase(iterator itr);

        //Erase Node in [from,to)
        iterator erase(iterator from,iterator to);

        void swap(List&);
    public:

        //template<typename Object>
        //friend typename List<Object>::Node* getPtr(const List<Object>& L, int k);
        friend List<Object>::Node* getPtr<Object>(List<Object>&, int);
        //frined declaration
    private:
        int theSize;            //LinkList's length
        Node *head;             //head sentinel of LinkList
        Node *tail;             //tail sentinel of LinkList

        void init();             //routine operation of initialize LinkList
    };



}

#endif // LINKLIST_H_INCLUDED
