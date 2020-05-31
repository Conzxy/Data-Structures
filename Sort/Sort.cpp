#include "List.h"

using namespace std;

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
        L[j+1]=temp;      //注意之前for的j--
      }
    }
}

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

void Merge(List &L,int low,int mid,int high)
{
    int i=low,j=mid+1;
    int k=0;
    int *temp=new int[high-low+1];
    while(i<=mid&&j<=high)
    {
      if(L[i]<=L[j])  //将第一子表放入temp
      {
        temp[k++]=L[i++];
      }
      else            //将第二子表放入temp
      {
        temp[k++]=L[j++];
      }
    }
    while(i<=mid)     //第一子表剩余的放入temp
    {
      temp[k++]=L[i++];
    }
    while(j<=high)    //第二子表剩余的放入temp
    {
      temp[k++]=L[j++];
    }
    for(k=0,i=low;i<=high;i++,k++)
    {
      L[i]=temp[k];   //拷贝temp
    }
    delete[]temp;
}

void MergeSort_top_to_bottom(List& L,int low,int high)
{
    int mid;
    if(low<high)  //子序列有两个及以上元素
    {
      mid=(low+high)/2;
      MergeSort_top_to_bottom(L,low,mid);     //对[low,mid]子序列排序
      MergeSort_top_to_bottom(L,mid+1,high);  //对[mid+1,high]子序列排序
      Merge(L,low,mid,high);    //合并两个子序列
    }
}

void MergePass(List &L,int length,int n)  //一趟二路归并（一个length对应一趟）
{
      int i;
      for(i=0;i+2*length-1<n;i=i+length*2)   //长度为length的两个子表归并
      {
        Merge(L,i,i+length-1,i+2*length-1);
      }
      if(i+length-1<n)        //剩余两个子表归并（后者长度小于length）
      {
        Merge(L,i,i+length-1,n-1);
      }
}

void MergeSort_bottom_to_top(List &L,int n)
{
    for(int length=1;length<n;length=2*length)
    {
      MergePass(L,length,n);
    }
}

void ShellSort(List &L)
{
    int i,j,temp;
    int d=L.size/2;
    while(d>0)
    {
      for(i=d;i<L.size;i++)
      {
        temp=L[i];
        for(j=i-d;j>=0&&temp<L[j];j-=d)
        {
          L[j+d]=L[j];
        }
        L[j+d]=temp;    //因为j-=d所以+d
      }
      d=d/2;
    }
}

void QuickSort(List &L,int left,int right)
{
    int l=left,r=right;
    int temp=L[left];
    if(l<r)
    {
      while(l!=r)
      {
        while(l<r&&L[r]>=temp)
        {
          r--;
        }
        L[l]=L[r];

        while(l<r&&L[l]<=temp)
        {
          l++;
        }
        L[r]=L[l];
      }
      L[l]=temp;
      QuickSort(L,left,l-1);
      QuickSort(L,l+1,right);
    }
}

void HeapAdjust(List &L,int i,int len)
{
      if(i>len/2-1)   //若无子树，直接退出
        return ;
      for(int k=2*i+1;k<len;k=2*k+1)
      {
        if(k+1<len&&L[k+1]>L[k])
        {
          k++;        //若右孩子比左孩子大，则替换
        }

        if(L[i]<L[k])
        {
          swap(L[i],L[k]);
          i=k;        //以最大子节点为当前结点
        }
        else
          break;      //若满足大堆性质，则直接退出
      }
}

void HeapSort(List &L)
{
    //从最后一个非叶子结点开始向前调整
    for(int i=L.size/2-1;i>=0;i--)
    {
      HeapAdjust(L,i,L.size);
    }

    //输出并再调整
    for(int j=L.size-1;j>0;j--)
    //j==0没有必要，因为此时只有一个根结点
    {
      swap(L[0],L[j]);
      HeapAdjust(L,0,j);
    }
}

void CountSort(List &L)
{
    int i;
    int min=L[0],max=L[0];
    for(i=1;i<L.size;i++)
    {
      if(L[i]>max)
      {
        max=L[i];
      }
      if(L[i]<min)
      {
        min=L[i];
      }
    }
    int range=max-min+1;
    int *count=new int[range];
    memset(count,0,sizeof(int)*range);

    for(i=0;i<L.size;i++)       //从原数组中取数，原数组个数为size
    {
      count[L[i]-min]++;
    }

    int index=0;
    for(i=0;i<range;i++)        //从开辟的数组中读取，开辟的数组大小为range
    {
      while(count[i]--)
        L[index++]=i+min;
    }
    delete[]count;
}

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

void Distribute(List &L,int k,list<int> *lists)
{
    for(int i=0;i<L.size;i++)
    {
      int index=Getkey(L[i],k);
      lists[index].push_back(L[i]);
    }
}

void Collect(List &L,list<int> *lists)
{
    int index=0;
    list<int>::iterator it;
    for(int i=0;i<10;i++)
    {
      it=lists[i].begin();
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
      Distribute(L,i,lists);
      Collect(L,lists);
    }
}
