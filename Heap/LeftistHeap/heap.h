//
// Created by Czxy on 2020/7/21.
//

#ifndef UNTITLED_HEAP_H
#define UNTITLED_HEAP_H

#include <iostream>
#include "dsexception.h"

template<typename Comparable>
class LeftistHeap
{
public:
    //default
    LeftistHeap():root{nullptr}{};
    //Big Five
    LeftistHeap(const LeftistHeap& rhs):root{rhs.root}
    {
        clone(rhs.root);
    }
    LeftistHeap(LeftistHeap&& rhs)noexcept
            :root{rhs.root}
    {
        rhs.root=nullptr;
    }
    ~LeftistHeap();

    LeftistHeap& operator=(const LeftistHeap& rhs);
    LeftistHeap& operator=(LeftistHeap&& rhs)noexcept ;

    //operations
    bool isEmpty()const;
    const Comparable &findMin()const;

    void insert(const Comparable &x);
    void insert(Comparable&& x);
    void deleteMin();
    void deleteMin(Comparable &MinItem);
    void makeEmpty();
    void merge(LeftistHeap &rhs);
    void InOrder();
private:
    struct LeftistNode{
        Comparable element;
        LeftistNode* left;
        LeftistNode* right;
        int npl;

        explicit LeftistNode(const Comparable &e,LeftistNode* l=nullptr,LeftistNode* r=nullptr,int n=0)
                :element{e},left{l},right{r},npl{n}{}
        explicit LeftistNode(Comparable&& e,LeftistNode* l=nullptr,LeftistNode* r=nullptr,int n=0)
                :element{std::move(e)},left{l},right{r},npl{n}{}
    };
    LeftistNode* root;

    LeftistNode* merge(LeftistNode* h1,LeftistNode* h2);
    LeftistNode* merge1(LeftistNode* h1,LeftistNode* h2);

    void swapChildren(LeftistNode* t);
    void reclaimMemory(LeftistNode* t);
    LeftistNode* clone(LeftistNode* t)const;

    void InOrder(LeftistNode *);
};

#endif //UNTITLED_HEAP_H
