# 插入排序
## 直接插入排序
![](https://img-blog.csdnimg.cn/20200617103202533.png)<br>
直接插入排序就是无序区有和有序区反序的元素，那么就将这个元素插入到有序区中合适的位置，使之成为有序区的元素<br>
![](https://img-blog.csdnimg.cn/20200617103306503.png)<br>
### 实现代码
```cpp
void InsertSort(List &L)
{
    int i,j;
    int temp;
    for(i=1;i<L.size;i++)
    {
      if(L[i-1]>L[i])     //发现反序元素
      {
        temp=L[i];        //临时变量记住要插入的元素
        for(j=i-1;j>=0&&L[j]>temp;j--)
        {
          L[j+1]=L[j];    //将有序区中比temp大的都右移，让出位置
        }
        L[j+1]=temp;        //注意之前for的j--
      }  
    }
}
```
## 算法复杂度
最好的情况（全都正序）：<br>
比较次数：n-1<br>
移动次数：0<br>
最坏的情况（全都反序）：<br>
比较次数：![](https://img-blog.csdnimg.cn/20200531122912813.gif)<br>
移动次数：![](https://img-blog.csdnimg.cn/20200531122912809.gif)<br>
平均比较和移动之和：
![](https://img-blog.csdnimg.cn/20200531122921926.gif)<br>
## 折半插入排序
![](https://img2018.cnblogs.com/blog/1475571/201908/1475571-20190815205421177-1703010007.png)<br>
相比直接插入在查找反序元素位置上提高了查找效率，移动数组元素次数不变，仅仅将分散移动变为集合移动。
### 实现代码
```cpp
void BinInsertSort(List &L)
{
  int i,j,temp;
  int low,high,mid;
  for(i=1;i<L.size;i++)
  {
    if(L[i-1]>L[i])
    {
      temp=L[i];
      low=0;
      high=i-1;

      while(low<=high)
      {
        mid=(low+high)/2;
        if(temp<L[mid])
          high=mid-1;
        else
          low=mid+1;
      }

      for(j=i-1;j>=high+1;j--)
      {
        L[j+1]=L[j];
      }
      L[high+1]=temp;
    }
  }
}
```
