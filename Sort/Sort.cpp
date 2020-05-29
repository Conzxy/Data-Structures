#include "List.h"

using namespace std;

void BubbleSort(List &L)
{

  int i,j;
  for(i=0;i<L.size;i++)
  {
    for(j=i;j<L.size;j++)
    {
      if(L.arr[i]>L.arr[j])
        swap(L.arr[i],L.arr[j]);
    }
  }
}
