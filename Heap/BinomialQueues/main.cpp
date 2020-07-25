#include <iostream>

#include "BinomialQ.h"
#include "Binomial_implement.h"
#include "dsexception.h"

using namespace std;

int main() {
    Binomial<int> h1;
    Binomial<int> h2;

    int x;
    int num;

    cin>>num;
    for(int i=0;i<num;i++)
    {
        cin>>x;
        h1.insert(x);
    }

    cin>>num;
    for(int i=0;i<num;i++)
    {
        cin>>x;
        h2.insert(x);
    }
    //h1.InOrder();
    //h2.InOrder();

    h1.merge(h2);
    h1.display();

}
