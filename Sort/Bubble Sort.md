# 冒泡排序
## 最简单的版本
```cpp
void BubbleSort(List &L)
{
  int i,j;
  for(i=0;i<L.size;i++)
  {
    for(j=i;j<L.size;j++)
    {
      if(L[i]>L[j])
        std::swap(L[i],L[j]);
    }
  }
}
```
但是很明显，这个算法是有缺陷的。除了相邻两个是有序的，其他的还是无序的。因此，需要优化算法。
## 内层循环优化
```cpp
void BubbleSort_in(List &L)
{
  int i,j;
  for(i=0;i<L.size;i++)
  {
    for(j=L.size-1;j>=i;j--)
    {
      if(L[j]>L[j+1])
      {
        std::swap(L[j],L[j+1]);
      }
    }
  }
}
```

## 外层循环优化
```cpp
void BubbleSort_out(List &L)
{
  int i,j;
  bool flag=true;
  for(i=0;i<L.size&&flag;i++)
  {
    for(j=L.size-1;j>=i;j++)
    {
      if(L[j]>L[j+1])
        {
          std::swap(L[j],L[j+1]);
          flag=false;
        }
    }
  }
}
```
## 算术复杂度
时间复杂度：O(n^2)
空间复杂度；O(1)
