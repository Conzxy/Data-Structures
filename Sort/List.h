#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#define MAXSIZE 100
#include <iostream>

class List
{
public:
    List()
    {
        int i = 0;
        while (std::cin >> arr[i])
        {
            i++;
            if (getchar() == '\n')
            {
                size = i;
                break;
            }
        }
    }
    int length() { return size; }
    int& operator[](int index) { return arr[index]; }

    //Sort functions
    friend void BubbleSort(List&);
    friend void BubbleSort_in(List&);
    friend void BubbleSort_out(List&);

    friend void SelectSort(List&);

    friend void InsertSort(List&);
    friend void BinInsertSort(List&);

    friend void MergeSort_top_to_bottom(List&,int,int);
    friend void MergeSort_bottom_to_top(List&,int,int);

private:
    int size=0;         //数组元素个数
    int arr[MAXSIZE];
};


#endif // LIST_H_INCLUDED
