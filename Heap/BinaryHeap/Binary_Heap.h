//
// Created by 谁敢反对宁宁，我就打爆他狗头！ on 2020/8/12.
//

#ifndef UNTITLED_BINARY_HEAP_H
#define UNTITLED_BINARY_HEAP_H

#include <vector>

namespace zxy{
    using namespace std;
    template<typename T>
    class BinaryHeap{
    public:
        explicit BinaryHeap(int capacity=100);
        explicit BinaryHeap(const vector<T>& items);

        bool isEmpty();
        const T& findMin();

        void insert(const T&);
        void insert(T&&);
        void deleteMin();
        void deleteMin(T&);
        void makeEmpty();
        void showHeap();
    private:
        int currentSize;
        vector<T> array;

        void buildHeap();
        void percolateDown(int);
    };
}

#endif //UNTITLED_BINARY_HEAP_H
