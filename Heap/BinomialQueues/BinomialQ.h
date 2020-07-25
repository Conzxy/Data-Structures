//
// Created by Czxy on 2020/7/23.
//

#ifndef UNTITLED_BINOMIALQ_H
#define UNTITLED_BINOMIALQ_H
#include <iostream>
#include <vector>


template<typename DataType>
class Binomial{
public:
    Binomial():theTrees(DEFAULT_TREES)
    {
        for(auto &root:theTrees)
            root=nullptr;
        currentSize=0;
    }
    Binomial(const DataType& e):theTrees(1),currentSize{1}
    {
        theTrees[0]=new BNode{e,nullptr,nullptr};
    }
    //copy and move constructor
    Binomial(const Binomial& rhs):theTrees{rhs.theTrees.size()},currentSize{rhs.currentSize}
    {
        for(int i=0;i<theTrees.size();i++)
            theTrees[i]=clone(rhs.theTrees[i]);
    }
    Binomial(Binomial&& rhs):theTrees{std::move(rhs.theTrees)},currentSize(rhs.currentSize)
    {}
    //assignment
    Binomial& operator=(const Binomial& rhs)
    {
        auto copy=rhs;
        std::swap(*this,copy);
        return *this;
    }
    Binomial& operator=(Binomial &&rhs)
    {
        std::swap(theTrees,rhs.theTrees);
        std::swap(currentSize,rhs.currentSize);
        return *this;
    }
    //destructor
    ~Binomial(){
        makeEmpty();
    }

    //interface
    void makeEmpty();               //析构
    void merge(Binomial &rhs);      //合并
    void insert(const DataType&);   //插入：合并的特殊情况
    void insert(DataType&&);

    void deleteMin();               //删除最小结点
    void deleteMin(DataType& minItem);

    bool isEmpty();
    const DataType& findMin()const;
    void display();
private:
    class BinomialNode;
    using BNode=BinomialNode;
    struct BinomialNode{
    DataType element;
    BinomialNode* leftchild;
    BinomialNode* nextSibling;

    explicit BinomialNode(const DataType& e,BNode* l=nullptr,BNode* n=nullptr)
    :element{e},leftchild{l},nextSibling{n}{}
    explicit BinomialNode(DataType&& e,BNode* l=nullptr,BNode* n=nullptr)
    :element{std::move(e)},leftchild{l},nextSibling{n}{}
};
    //member data
    std::vector<BNode*> theTrees;
    int currentSize;

    //class constant
    const static int DEFAULT_TREES=1;

    //实现细节
    int capacity()const;
    int findMinIndex()const;
    BNode* combineTrees(BNode*,BNode*);
    void makeEmpty(BNode* &t);
    BNode* clone(BNode*)const;  //不需要const，我们得到的是副本
    void display(BNode*);
};
#endif //UNTITLED_BINOMIALQ_H
