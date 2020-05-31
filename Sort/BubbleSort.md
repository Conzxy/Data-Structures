# 冒泡排序
## 基本思想
冒泡排序分为趟数和交换次数。<br>
外层循环为趟数，如果有n个元素则要循环n-1趟。<br>
内层循环主要做每一趟的交换，从第0个元素开始如果发现当前元素大于它的后一个元素，将其交换，每一趟下来，前面的有序区新增一个最小值（相比无序区最小），然后在无序区的第一个元素开始到最后一个元素冒泡排序，将最小值冒出来，以此循环。
## 最简单的版本
```cpp
void BubbleSort(List &L)
{
  int i,j;
  for(i=0;i<L.size-1;i++)
  {
    for(j=i+1;j<L.size;j++)
    {
      if(L[i]>L[j])
        swap(L[i],L[j]);
    }
  }
}
```
严格意义上，这并不能称得上冒泡排序，因为不是比较两个相邻元素，而是直接拿第i个元素和第j个元素对比，这样的话对第i个元素之后的序列没什么帮助。<br>
![](https://img-blog.csdnimg.cn/20200531005611411.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3p4eTAxMjM0MA==,size_16,color_FFFFFF,t_70)<br>
## 第一层优化
```cpp
void BubbleSort_each(List &L)
{
  int i,j;
  for(i=0;i<L.size-1;i++)
  {
    for(j=L.size-2;j>=i;j--)
    {
      if(L[j]>L[j+1])
      {
        swap(L[j],L[j+1]);
      }
    }
  }
}
```
相邻两个交换，可以尽量使得除有序区元素外的元素不像上面那么无序<br>
![](https://img-blog.csdnimg.cn/20200531005611464.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3p4eTAxMjM0MA==,size_16,color_FFFFFF,t_70)<br>
第一趟把2提到了第三位<br>
![](https://img-blog.csdnimg.cn/20200531005611362.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3p4eTAxMjM0MA==,size_16,color_FFFFFF,t_70)<br>
第二趟把3提到了第四位<br>
数据越多，相邻交换的优势越大。
## 进一步优化
```cpp
void BubbleSort_flag(List &L)
{
  int i,j;
  bool flag=true;
  for(i=0;i<L.size-1&&flag;i++)
  {
    flag=false;
    for(j=L.size-2;j>=i;j--)
    {
      if(L[j]>L[j+1])
        {
          swap(L[j],L[j+1]);
          flag=true;
        }
    }
  }
}
```
通过设置flag来阻止对已排序序列的循环判断<br>
![](https://img-blog.csdnimg.cn/2020053109350248.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3p4eTAxMjM0MA==,size_16,color_FFFFFF,t_70)<br>
## 算术复杂度
最好的情况（全部都是正序的情况下）:<br>
比较次数：n-1；<br>
移动次数：0（无数据交换）<br>
最差的情况（全部都是反序的情况下）：<br>
比较次数：![](https://img-blog.csdnimg.cn/20200531100150737.gif)<br>
移动次数:同上<br>
综上，时间复杂度：O(n^2)<br>
空间复杂度；O(1)
