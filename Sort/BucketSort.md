# 桶排序
## 基本思想
桶排序的思想近乎彻底的分治思想。<br>
桶排序假设待排序的一组数均匀独立的分布在一个范围中，并将这一范围划分成几个子范围（桶）。<br>
然后基于某种映射函数f ，将待排序列的关键字 k 映射到第i个桶中 (即桶数组B 的下标i) ，那么该关键字k 就作为 B[i]中的元素 (每个桶B[i]都是一组大小为N/M 的序列 )。<br>
接着将各个桶中的数据有序的合并起来 : 对每个桶B[i] 中的所有元素进行比较排序 (可以使用快排)。然后依次枚举输出 B[0]….B[M] 中的全部内容即是一个有序序列。<br>
补充： 映射函数一般是 f = array[i] / k; k^2 = n; n是所有元素个数<br>
为了使桶排序更加高效，我们需要做到这两点：<br>
在额外空间充足的情况下，尽量增大桶的数量<br>
使用的映射函数能够将输入的 N 个数据均匀的分配到 K 个桶中<br>
同时，对于桶中元素的排序，选择何种比较排序算法对于性能的影响至关重要。<br>
## 实现代码
```cpp
void BucketSort(List &L)
{
    int i,j;
    int max=L[0];
    for(int i=1;i<L.size;i++)
    {
      if(L[i]>max)
        max=L[i];
    }

    int range=max/10+1;
    vector<int> *Buckets=new vector<int>[range];
    for(i=0;i<L.size;i++)
    {
      int change=L[i]/10;
      Buckets[change].push_back(L[i]);
    }
    for(i=0;i<range;i++)
    {
      if(Buckets[i].size()>0)
      {
        sort(Buckets[i].begin(),Buckets[i].end());
      }
    }
    int index=0;
    for(i=0;i<range;i++)
    {
      for(j=0;j<Buckets[i].size();j++)
      {
        L[index++]=Buckets[i][j];
      }
    }
    delete[]Buckets;
}
```
