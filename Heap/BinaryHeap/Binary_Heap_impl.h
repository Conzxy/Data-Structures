//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2020/8/13.
//

#ifndef UNTITLED_BINARY_HEAP_IMPL_H
#define UNTITLED_BINARY_HEAP_IMPL_H

#include <iostream>
#include "Binary_Heap.h"
#include "dsexception.h"

namespace zxy{
    template<typename T>
    BinaryHeap<T>::BinaryHeap(int capacity):
    array(capacity+1),currentSize(0){}//array[0]是哨兵

    template<typename T>
    BinaryHeap<T>::BinaryHeap(const vector<T>& items):array(items.size()+10),currentSize{items.size()}
    {
        for(int i=0;i!=currentSize;i++)
        {
            array[i+1]=items[i];
        }
        buildHeap();
    }

    template<typename T>
    bool BinaryHeap<T>::isEmpty() {
        return currentSize==0;
    }

    template<typename T>
    const T& BinaryHeap<T>::findMin() {
        if(isEmpty())
            throw UnderflowException{};
        return array[1];
    }

    template<typename T>
    void BinaryHeap<T>::insert(const T& x)
    {
        if(currentSize+1==array.size())
            array.resize(2*array.size());   //扩容

        /*
         * 上滤操作（percolate up）：与下滤操作类似，但是不是调整根结点，而是child。
         * hole是新增位置的child，其parent是最后一个父结点，通过父结点不断往上爬直到
         * 欲插入值不小于父结点停止。
         * 最后用储存插入值的哨兵填上hole。
         */
        int hole=++currentSize;
        T copy=x;

        array[0]=std::move(copy);
        for(;x<array[hole/2];hole/=2)
            array[hole]=std::move(array[hole/2]);//x<parent，hole percolate up
        array[hole]=std::move(array[0]);
    }

    template<typename T>
    void BinaryHeap<T>::insert(T&& x)
    {
        if(currentSize+1==array.size())
            array.resize(2*array.size());

        int hole=++currentSize;
        T copy=x;

        array[0]=std::move(copy);
        for(;x<array[hole/2];hole/=2)
            array[hole/2]=std::move(array[hole]);
        array[hole]=std::move(array[0]);
    }

    template<typename T>
    void BinaryHeap<T>::deleteMin() {
        if(isEmpty())
            throw UnderflowException{};

        array[1]=std::move(array[currentSize--]);
        percolateDown(1);
    }

    template<typename T>
    void BinaryHeap<T>::deleteMin(T &Minitem) {
        if(isEmpty())
            throw UnderflowException{};

        Minitem=std::move(array[1]);
        array[1]=std::move(array[currentSize--]);
        percolateDown(1);
    }

    template<typename T>
    void BinaryHeap<T>::makeEmpty() {
        currentSize=0;
    }

    /*
     * 下滤操作：调整失衡点（不满足堆序性质），以失衡点为根结点，在子树中找到满足堆序的位置。
     * 方式：通过child挖hole，如果最小child<失衡点，那么最小child成为失衡点的parent，原来位置成为hole，
     * 如此反复，得到一个“下滤”的形态。如果到达leaf层或已经满足堆序（到达leaf层自然满足），即可终止循环。
     * 最后用储存原来失衡点的局部变量来填上hole。
     */
    template<typename T>
    void BinaryHeap<T>::percolateDown(int hole) {
        int child;
        T tmp=std::move(array[hole]);

        for(;hole*2<=currentSize;hole=child)
        {
            child=hole*2;
            if(child!=currentSize&&array[child+1]<array[child])
                ++child;    //找到最小child
            if(array[child]<tmp)
                array[hole]=std::move(array[child]);
            else
                break;  //如果array[child]>=tmp,此时已满足minheap的性质
        }
        array[hole]=std::move(tmp);
    }

    /*建堆操作：从最后一个根结点开始建堆，因为每个根结点都是不平衡状态*/
    template<typename T>
    void BinaryHeap<T>::buildHeap(){
        for(int i=currentSize/2;i>0;i--)
            percolateDown(i);
    }

    template<typename T>
    void BinaryHeap<T>::showHeap() {
        int cnt=1;
        for(int i=1;i<=currentSize;i++)
        {
            cout<<array[i]<<" ";
            if(i==(1<<cnt)-1)
            {
                cout<<endl;
                ++cnt;
            }

        }
    }
}



#endif //UNTITLED_BINARY_HEAP_IMPL_H
