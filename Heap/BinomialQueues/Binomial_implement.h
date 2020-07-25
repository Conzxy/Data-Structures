//
// Created by Czxy on 2020/7/24.
//

#include <iostream>
#include "BinomialQ.h"
#include <algorithm>
#include "dsexception.h"
template <typename T>
int Binomial<T>::capacity() const {
    return (1<<theTrees.size())-1;
}

template <typename T>
int Binomial<T>::findMinIndex()const{
    int minIndex;
    int i;

    for(i=0;theTrees[i]==nullptr;i++)
        ;
    for(minIndex=i;i<theTrees.size();i++)
        if(theTrees[i]!=nullptr&&theTrees[i]->element<theTrees[minIndex]->element)
            minIndex=i;
    return minIndex;
}

template<typename T>
const T& Binomial<T>::findMin()const{
    int minIndex=findMinIndex();
    return theTrees[minIndex]->element;
}

template<typename T>
void Binomial<T>::makeEmpty(BNode* &t)
{
    if(t!=nullptr)
    {
        makeEmpty(t->leftchild);
        makeEmpty(t->nextSibling);
        delete t;
        t=nullptr;
    }
}

template<typename T>
typename Binomial<T>::BNode* Binomial<T>::combineTrees(BNode *t1, BNode *t2) {
    if(t1->element>t2->element)
        return combineTrees(t2,t1);
    t2->nextSibling=t1->leftchild;
    t1->leftchild=t2;
    return t1;
}

template<typename T>
typename Binomial<T>::BNode* Binomial<T>::clone(BNode* t)const
{
    if(t==nullptr)
        return nullptr;
    else{
        return new BNode{t->element,clone(t->leftchild),clone(t->nextSibling)};
    }
}

template<typename T>
void Binomial<T>::makeEmpty()
{
    currentSize=0;
    for(auto &root:theTrees)
        makeEmpty(root);
}

template<typename T>
bool Binomial<T>::isEmpty() {
    return currentSize==0;
}

template<typename T>
void Binomial<T>::merge(Binomial<T> &rhs) {
    if(this==&rhs)
        return ;

    currentSize+=rhs.currentSize;
    if(currentSize>capacity())
    {
        int oldNumTrees=theTrees.size();
        int newNumTrees=std::max(theTrees.size(),rhs.theTrees.size())+1;
        theTrees.resize(newNumTrees);
        for(int i=oldNumTrees;i<newNumTrees;i++)
        {
            theTrees[i]=nullptr;
        }
    }

    BNode *carry=nullptr;

    for(int i=0,j=1;j<=currentSize;i++,j*=2)
    {
        BNode* t1=theTrees[i];
        BNode* t2=i<rhs.theTrees.size()?rhs.theTrees[i]:nullptr;


        int whichcase=t1==nullptr?0:1;
        whichcase+=t2==nullptr?0:2;
        whichcase+=carry==nullptr?0:4;

        switch(whichcase)
        {
            case 0:/*No Trees*/
            case 1:/*only this*/
                break;
            case 2:/*only rhs*/
                theTrees[i]=t2;
                rhs.theTrees[i]=nullptr;
                break;
            case 4:/*only carry*/
                theTrees[i]=carry;  //浅拷贝，转让资源管理权
                carry=nullptr;
                break;
            case 3:/*this and rhs*/
                carry=combineTrees(t1,t2);
                theTrees[i]=rhs.theTrees[i]=nullptr;
                break;
            case 5:/*this and carry*/
                carry=combineTrees(t1,carry);
                theTrees[i]=nullptr;
                break;
            case 6:/*rhs and carry*/
                carry=combineTrees(t2,carry);
                rhs.theTrees[i]=nullptr;
                break;
            case 7:/*all three*/
                theTrees[i]=carry;
                carry=combineTrees(t1,t2);
                rhs.theTrees[i]=nullptr;
                break;
        }
    }

    for(auto &root:rhs.theTrees)
        root=nullptr;
    rhs.currentSize=0;

}

template<typename T>
void Binomial<T>::insert(const T& x)
{
    Binomial oneItem{x};
    merge(oneItem);
}

template<typename T>
void Binomial<T>::insert(T&& x)
{
    Binomial oneItem{std::move(x)};
    merge(oneItem);
}

template<typename T>
void Binomial<T>::deleteMin(T& minItem)
{
    if(isEmpty())
        throw UnderflowException{};

    int minIndex=findMinIndex();
    minItem=theTrees[minIndex]->element;

    BNode* oldroot=theTrees[minIndex];
    BNode* deleteTrees=oldroot->leftchild;
    delete oldroot;
    theTrees[minIndex]=nullptr;

    //construct H''
    Binomial deleteQueue;
    deleteQueue.theTrees.resize(minIndex);
    deleteQueue.currentSize=(1<<minIndex)-1;
    for(int i=minIndex-1;i>=0;i--)
    {
        deleteQueue.theTrees[i]=deleteTrees;
        deleteTrees=deleteTrees->nextSibling;
        deleteQueue.theTrees[i]->nextSibling=nullptr;
    }

    //consturct H'
    currentSize-=deleteQueue.currentSize+1;

    merge(deleteQueue);
}

template<typename T>
void Binomial<T>::deleteMin()
{
    T x;
    deleteMin(x);
}

template<typename T>
void Binomial<T>::display(BNode* root)
{
    /**
     * ********儿子编号
     * 儿子内容
     * ********儿子编号
     *
     * --------儿子编号j+兄弟编号i。表示第j个儿子的第i个兄弟
     * --------
     *
     */
    if(root!=nullptr)
    {
        /*int j=1;
        std::cout<<root->element<<" ";
        while(root->leftchild)
        {
            int i=1;
            root=root->leftchild;
            auto oldroot=root;
            std::cout<<"\n*************************"<<j;
            std::cout<<"\n儿子"<<j<<"："<<root->element<<std::endl;

            while(root->nextSibling)
            {
                root=root->nextSibling;
                if(root->leftchild)
                {
                    std::cout<<"     兄弟"<<i<<"（有儿子）："<<std::endl;
                    std::cout<<"----------------------------------"<<j<<i<<std::endl;
                    display(root);
                    std::cout<<"----------------------------------"<<j<<i<<std::endl;
                }
                else{
                    std::cout<<"     兄弟"<<i<<"："<<root->element<<" ";
                }
                i++;
            }
            root=oldroot;
            std::cout<<"\n*************************"<<j<<std::endl;
            j++;
        }*/
        std::cout<<root->element<<" ";
        display(root->leftchild);
        display(root->nextSibling);


    }
}

template<typename T>
void Binomial<T>::display()
{
    for(int i=0;i<theTrees.size();i++)
        if(theTrees[i]!=nullptr)
        {
            std::cout<<"第"<<i<<"阶的二项树:"<<std::endl;
            display(theTrees[i]);
            std::cout<<std::endl;
        }
}
