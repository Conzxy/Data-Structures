# 并查集（Union-Find Set）
## 概念
并查集正如其名，分为**Union**和**Find**,即合并和查找。<br>

### 代表元
我们用集合中某个元素来代表这个集合，称为**代表元**。
一个集合中的所有元素形成以代表元为根结点的树形结构。
对于每一个元素parent[x]指向x在树形结构中的父节点，如果x是根结点，则令parent[x]=x。<br>
### 查找操作
就是依据parent[x]一路往上爬，最后找到代表元，从而确定自己所在的集合。<br>

### 路径压缩（查找优化）
为了加快查找速度，我们把x到根结点上的路径上的所有结点的parent都设为根结点。<br>

## 基本操作
一般，并查集分三个操作

### 初始化
对所有单个数据建立一个单独的集合（即根据题目的意思自己建立的最多可能有的集合，为下面的合并查找操作提供操作对象）<br>
一般来说，每一个单个的集合有三个要素：<br>
* 集合所代表的数据（自定义）
* 集合的层次，用rank表示（初始化一般将rank都初始化为0）
* 集合的类别，用parent或是set表示（用指针指示）

初始化的时候，一个集合的parent都是这个集合自己的标号。没有跟它同类的集合，那么这个集合的源头只能是自己了。
### 查找函数
查找就是要找到parent的源头，
```cpp
int Find(int i)
{
    if(fa[i]==i)
      return i;
    else
      Find(fa[i]);
}
```
路径压缩：
```cpp
int UniFind(int a)
{
    int root=a;

    while(root!=fa[a]) //Find the root
      root=set[a];

      while(a!=root)      //compress the path
      {
        int parentof_a=fa[a];  //记录a的父结点
        fa[a]=root;            //令当前结点的父节点为root
        a=parentof_a;
      }

      return root;
}
```
还有一种递归写法：
```cpp
int UniFind(int a)
{
    return fa[a]==a?a:(fa[a]=UniFind(fa[a]));
}
```

### 合并操作
![](https://img-blog.csdnimg.cn/20200611162913766.png)<br>
最简单的合并只涉及代表元：<br>
```cpp
void Union(int i,int j)
{
  int x=Find[i];
  int y=Find[j];
  if(x==y)  return ;
  else
    fa(x)=y;//or fa[y]=x;
    //没有考虑rank

}
```

若涉及rank，则如下：<br>
```cpp
void Union(int a,int b)
{
    int x=Find[a];
    int y=Find[b];
    if(x==y) return;
    if(rank[x]>rank[y])
      fa[y]=x;
    else
    {
      if(rank[x]==rank[y]) rank[y]++;//新结点的深度加1
      fa[x]=y;
    }
}
```
rank小的向rank大的靠拢，以至于树不会退化严重。
