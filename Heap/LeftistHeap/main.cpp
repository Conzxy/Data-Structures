#include <iostream>
#include "heap.h"
#include "heapi.h"
#include "dsexception.h"

using namespace std;

int main() {
    LeftistHeap<int> h1;
    h1.insert(3);
    h1.insert(10);
    h1.insert(8);
    h1.insert(21);
    h1.insert(14);
    h1.insert(23);
    h1.insert(17);
    h1.insert(26);
    h1.InOrder();
    cout<<endl;
    LeftistHeap<int> h2;
    h2.insert(6);
    h2.insert(12);
    h2.insert(7);
    h2.insert(18);
    h2.insert(24);
    h2.insert(37);
    h2.insert(18);
    h2.insert(33);
    h2.InOrder();
    cout<<endl;
    h1.merge(h2);
    h1.InOrder();
    cout<<endl;
    try{
        h2.findMin();
    }
    catch(UnderflowException)
    {
        cout<<h1.findMin();
    }
    return 0;
}
