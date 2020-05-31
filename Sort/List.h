#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#define MAXSIZE 100
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <memory.h>
#include <algorithm>

using std::ifstream;using std::list;using std::vector;
using std::cin;using std::cout;using std::swap;using std::sort;

class List
{
public:
    List()  //构造函数
    {
        int i = 0;
        ifstream fin("test.txt");
        while (!fin.eof())
        {
            fin >> arr[i];
            i++;
            size=i;
            /*if (getchar() == '\n')
            {
                size = i;
                break;
            }*/
        }
    }

    int length() { return size; }
    int& operator[](int index) { return arr[index]; }

    //Sort functions
    friend void BubbleSort(List&);
    friend void BubbleSort_each(List&);
    friend void BubbleSort_flag(List&);

    friend void SelectSort(List&);

    friend void InsertSort(List&);
    friend void BinInsertSort(List&);

    friend void MergeSort_top_to_bottom(List&,int,int);
    friend void MergeSort_bottom_to_top(List&,int);

    friend void ShellSort(List&);

    friend void QuickSort(List&,int,int);

    friend void HeapSort(List&);

    friend void CountSort(List&);

    friend void BucketSort(List&);

    friend void RadixSort(List&);

    friend void Merge(List&,int,int,int);
    friend void MergePass(List&,int,int);

    friend void HeapAdjust(List&,int,int);

    friend int Getkey(int,int);
    friend void Distribute(List&,int,list<int>*);
    friend void Collect(List&,list<int>*);

private:
    int size;         //数组元素个数
    int arr[MAXSIZE];

};



#endif // LIST_H_INCLUDED
