#include <iostream>
#include "Binary_Heap_impl.h"
using namespace zxy;

int main(){
    BinaryHeap<int> hp({13,14,16,19,21,19,68,65,26,32,31});
    hp.showHeap();
    hp.deleteMin();
    cout<<endl;
    hp.showHeap();
}
