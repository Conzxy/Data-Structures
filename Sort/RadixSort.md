# 基数排序
## 基本思想
基数排序分为两个步骤：分配（Distribute）和收集（Collect）<br>
分配是指分配一个存储链表的数组，第一个元素（链表）存储该位数上是0的元素，依次类推，共10个元素。<br>
收集是指将链表上的元素收集到原数组中。<br>
经过所有分配，最后收集到的一定是有序的。
## 例子
![](https://img2018.cnblogs.com/blog/1475571/201908/1475571-20190815221101602-1916860041.png)<br>
这是对三位数的基数排序流程，要经过所有位的分配和收集。其最后收集到的数组是排序好的。
## 实现代码
```cpp
int Getkey(int value,int k) //第k位的数
{
    int key;
    while(k>0)
    {
      key=value%10;
      value/=10;
      k--;
    }
    return key;
}

void Distribute(List &L,int k,list<int> lists)
{
    for(int i=0;i<L.size;i++)
    {
      int index==Getkey(L[i],k);
      lists.[index].push_back(L[i]);
    }
}

void Collect(List &L,list<int> lists)
{
    int index=0;
    list<int>::iterator it;
    for(int i=0;i<10;i++)
    {
      it=lists[i].begin()
      while(it!=lists[i].end())
      {
        L[index++]=*(it++);
      }
      lists[i].clear();
    }
}

void RadixSort(List &L)
{
    int k=3;
    list<int> lists[10];
    for(int i=1;i<=k;i++)
    {
      Disbute(L,i,lists);
      Collect(L,lists);
    }
}
```
