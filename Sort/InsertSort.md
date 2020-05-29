# 插入排序
## 直接插入排序
![](https://img2018.cnblogs.com/blog/1475571/201908/1475571-20190815204657643-1362081037.png)
直接插入排序就是无序区有和有序区反序的元素，那么就将这个元素插入到有序区中合适的位置，使之成为有序区的元素
![](https://img2018.cnblogs.com/blog/1475571/201908/1475571-20190815204529830-1630116127.png)
### 实现代码
```cpp
void InsertSort(List &L)
{
    int i,j;
    int temp;
    for(i=1;i<L.size;i++)
    {
      if(L[i-1]>L[i])
      {
        temp=L[i];
        for(j=i-1;j>=0&&L[j]>temp;j--)
        {
          L[j+1]=L[j];
        }
      }
      a[j+1]=temp;
    }
}
```

## 折半插入排序
![](https://img2018.cnblogs.com/blog/1475571/201908/1475571-20190815205421177-1703010007.png)
相比直接插入仅仅在查找反序元素位置上提高了查找效率，移动数组元素照旧
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
