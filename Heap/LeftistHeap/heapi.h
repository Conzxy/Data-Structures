//
// Created by Czxy on 2020/7/21.
//

#ifndef UNTITLED_HEAPI_H
#define UNTITLED_HEAPI_H

#include <iostream>
#include "dsexception.h"
#include "heap.h"
using namespace std;

template<typename Comparable>
LeftistHeap<Comparable>::~LeftistHeap()
{
    makeEmpty();
}

template<typename Comparable>
LeftistHeap<Comparable>& LeftistHeap<Comparable>::operator=(const LeftistHeap& rhs)
{
    using std::swap;
    LeftistHeap copy=rhs;
    swap(*this,copy);
    return *this;
}

template<typename Comparable>
LeftistHeap<Comparable>& LeftistHeap<Comparable>::operator=(LeftistHeap&& rhs)noexcept
{
    std::swap(root,rhs.root);
    return *this;
}

template<typename Comparable>
bool LeftistHeap<Comparable>::isEmpty()const
{
    return root==nullptr;
}

template<typename Comparable>
const Comparable & LeftistHeap<Comparable>::findMin()const {
    if(isEmpty())
        throw UnderflowException{};
    return root->element;
}

template<typename Comparable>
void LeftistHeap<Comparable>::insert(const Comparable &x)
{
    root=merge(new LeftistNode{x},root);
}

template<typename Comparable>
void LeftistHeap<Comparable>::insert(Comparable &&x)
{
    root=merge(new LeftistNode{std::move(x)},root);
}

template<typename Comparable>
void LeftistHeap<Comparable>::deleteMin()
{
    if(isEmpty())
        throw UnderflowException{};

    LeftistNode* oldroot=root;
    root=merge(root->left,root->right);
    delete oldroot;
}

template<typename Comparable>
void LeftistHeap<Comparable>::deleteMin(Comparable &MinItem)
{
    MinItem=findMin();
    deleteMin();
}

template<typename Comparable>
void LeftistHeap<Comparable>::makeEmpty()
{
    reclaimMemory(root);
    root=nullptr;
}

template<typename Comparable>
void LeftistHeap<Comparable>::merge(LeftistHeap &rhs)
{
    if(this==&rhs)    //identity test
        return ;
    root=merge(root,rhs.root);
    rhs.root=nullptr;       //置为nullptr，将资源管理权转交给合并后的heap，避免double free
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode *
LeftistHeap<Comparable>::merge(LeftistNode* h1,LeftistNode* h2)
{
    if(h1==nullptr)
        return h2;
    if(h2==nullptr)
        return h1;
    if(h1->element<h2->element)
        return merge1(h1,h2);
    else
        return merge1(h2,h1);
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode *
LeftistHeap<Comparable>::merge1(LeftistNode *h1, LeftistNode *h2)
{
    if(h1->left==nullptr) //a single node
        h1->left=h2;
    else{
        h1->right=merge(h1->right,h2);
        if(h1->left->npl<h1->right->npl)
            swapChildren(h1);
        h1->npl=h1->right->npl+1;
    }
    return h1;
}

template<typename Comparable>
void LeftistHeap<Comparable>:: swapChildren(LeftistNode *t)
{
    LeftistNode *tmp = t->left;
    t->left = t->right;
    t->right = tmp;
}

template<typename Comparable>
void LeftistHeap<Comparable>::reclaimMemory(LeftistNode *t)
{
    if(t!=nullptr) {
        reclaimMemory(t->left);
        reclaimMemory(t->right);
        delete t;
    }
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode *
LeftistHeap<Comparable>:: clone(LeftistNode *t)const {
    if(t==nullptr)
        return nullptr;
    else
        return new LeftistNode{t->element,clone(t->left),clone(t->right),t->npl};
}

template<typename Comparable> void
LeftistHeap<Comparable>::InOrder(LeftistNode *root) {
    if(root!=nullptr)
    {
        InOrder(root->left);
        std::cout<<root->element<<" ";
        InOrder(root->right);
    }
}

template<typename Comparable> void
LeftistHeap<Comparable>::InOrder()
{
    InOrder(root);
}

#endif //UNTITLED_HEAPI_H
