# 选择排序
## 基本思想
![](https://img2018.cnblogs.com/blog/1475571/201908/1475571-20190815213627230-1753040981.png)<br>
默然未排序区的首个元素为最小，然后与后面的最小元素交换，直至循环完成
## 实现代码
```cpp
void SelectSort(List &L)
{
  int i,j;
  int minIndex=i;   //未排序首位元素
  for(i=0;i<L.size;i++)
  {
    minIndex=i;
    for(j=i+1;j<L.size;j++)
    {
      if(L[minIndex]>L[j])
          min=j;
    }
  }
}
```
## 算法复杂度
时间复杂度：O(n^2)
空间复杂度：O(1)
