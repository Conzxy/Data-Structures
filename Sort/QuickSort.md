# 快速排序
## 基本思想
每趟使表的第1个元素放入适当位置（归位），并且左边的元素小于这个元素，右面的元素大于这个元素，将表一分为二，对子表按递归方式继续这种划分，直至划分的子表长为0或1（递归出口）。
![](https://img2018.cnblogs.com/blog/1475571/201908/1475571-20190815212143800-1869313412.png)<br>
快速排序二叉递归树：<br>
![](https://img2018.cnblogs.com/blog/1475571/201908/1475571-20190815212307728-17746403.png)<br>

顺带一提，STL的sort的实现原理就是快速排序。
## 实现代码
```cpp
void QuickSort(List &L,int left,int right)
{
    int l=left,r=right;
    int temp=L[left];
    if(l<r)
    {
      while(l!=r)
      {
        while(l<r&&L[l]<temp)
        {
          l++;
        }
        L[r]=temp;

        while(l<r&&L[r]>temp)
        {
          r--;
        }
        L[l]=temp;
      }
      L[l]=temp;
      QuickSort(L,left,l-1);
      QuickSort(L,l+1,right);
    }
}
```
