# 选择排序
## 基本思想
![](https://img2018.cnblogs.com/blog/1475571/201908/1475571-20190815213627230-1753040981.png)<br>
默然未排序区的首个元素为最小，然后与后面的最小元素交换，直至循环完成
## 实现代码
```cpp
void SelectSort(List &L)
{
  int i,j;
  int minIndex=i;   
  for(i=0;i<L.size-1;i++) //做第i趟排序,共n-1趟，因为第n趟只剩一个一定是最大的
  {
    minIndex=i;
    for(j=i+1;j<L.size;j++)
    {
      if(L[minIndex]>L[j])
          minIndex=j;
    }
    if(minIndex!=i)
      swap(L[minIndex],L[i]);
  }
}
```
## 算法复杂度
从i个记录中挑选最小记录需要比较i-1次。<br>
第i（i=0～n-2）趟从n-i记录中挑选最小记录需要比较n-i-1。<br>
对 n 个记录进行简单选择排序，所需进行的关键字的比较次数 总计为：<br>
![](https://img-blog.csdnimg.cn/20200531163304491.gif)<br>
移动记录的次数，正序为最小值 0，反序为最大值n-1 。<br>
综上，简单选择排序的最好、最坏和平均时间复杂度为O(n2)。
