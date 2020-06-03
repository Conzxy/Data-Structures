# Kruskal
kruskal与prim不同，是基于边去构造最小生成树，所以适用于边比较少的稀疏图。<br>
kruskal需要边的集合，我们称其为边集数组。边集数组按从小到大的顺序排序，方便构造最小生成树。<br>
## 边集数组
结构体
```cpp
template<typename T,typename E>
struct EdgeInf
{
  int begin;  //头部
  int end;    //尾部
  E edgeweight; //权值
  bool operator<(EdgeInf const& rhs)
  {
    return this->edgeweight<rhs.edgeweight;
  }//sort的比较器//隐式谓词
}
```
边集数组构造函数
```cpp
vector<EdgeInf<T,E>> Matrix::edgeinfo()
{
    vector<EdgeInf<T,E>> edgeIfo;
    EdgeInf<T,E> sedge;
    if(!Directed) //无向
    {
      for(int i=0;i<_num_Vertexes;i++)
        for(int j=i+1;i<_num_Vertexes;j++)  //无向图对称
          if(edge[i][j]!=0&&edge[i][j]!=_max_Weight)
          {
            sedge.begin=i;
            sedge.end=j;
            sedge.edgeweight=edge[i][j];
            edgeIfo.push_back(sedge);
          }
    }
    else{
      for(int i=0;i<_num_Vertexes;j++)
        for(int j=0;j<_num_vertexes;j++)
          if(edge[i][j]!=0&&edge[i][j]!=_max_Weight)
          {
            sedge.begin=i;
            sedge.end=j;
            sedge.edgeweight=edge[i][j];
            edgeIfo.push_back(sedge);
          }
    }
    sort(edgeIfo.begin(),edgeIfo.end());  //调用sort进行排序（QuickSort）
    return edgeIfo;
}
```

## 构造最小生成树
边集数组构造好，vector中根据权值从小到大排序。我们沿着下标选择begin和end连线来构造最小生成树，但是，在连接过程中可能出现成环的现象，这是由于父节点重复了，孩子想与父节点连在一起或是孩子想连在一起而造成的一种严重错误。<br>
我们可以通过一个parent数组来储存下标对应顶点的父节点，从而避免自环的情况。<br>
```cpp
vector<int> parent(numvertexes,0);
int Find(vector<int> parent,int f)
{
  if(parent>0)  //找到当前树的根结点，没有直接返回连线尾部顶点
    f=parent[f];
  return f;
}
```
Kruskal
```cpp
void MinispanTreeKruskal(int numvertex,int numedge,vector<EdgeInf<string,int>> &edgeInf,vector<EdgeInf<string,int>> &finaledge)
{
  int m,n;
  int parent(numvertex,0);  //初始化parent
  for(int i=0;i<numvertex;i++){
    m=Find(parent,edgeInf[i].begin);
    n=Find(parent,edgeInf[i].end);
    if(m!=n)  //不相等表示父节点不是同一个，那么就不会出现自环现象
    {
      parent[m]=n;  //两树合并，新加入的结点成为新的根结点(单一的根结点当然也是树)
      finaledge.push_back(edgeInf[i]);
    }
  }
}
```
n=m说明了有两颗树，它们的根结点是相同的，那么它们就是连通的，如果再添上一笔连接在一起就会形成环，而这正是我们要避免的。<br>
而parent[m]=n的作用就是将一个个没有连通的树或结点连接在一起，最后形成最小生成树。<br>
## 实例讲解
![](https://img-blog.csdnimg.cn/20200603093015119.png)<br>
边集数组为：<br>

|edgeInf|begin|end|edgeweight|
|-------|-----|---|----------|
|0|4 |7 |7 |
|1|2|8|8|
|2|0|1|10|
|3|0|5|11|
|4|1|8|12|
|5|1|6|16|
|6|3|7|16|
|7|5|6|17|
|8|1|2|18|
|9|6|7|19|
|10|3|4|20|
|11|3|8|21|
|12|2|3|22|
|13|3|6|24|
|14|4|5|26|

1）4，7正常连线，v7成为v4的父结点<br>
2）2，8正常连线，v8成为v2的父结点<br>
3）0，1正常连线，v1成为v0的父结点<br>
4）0，5，v0的父节点是v1，正常连线，v5与v0所在树合并，v5成为新的根结点<br>
5）1，8，v1的根结点是v5，正常连线，v8与v1所在树合并，v8成为新的根结点<br>
6）1，6，v1父结点是v8，正常连线，与v6合并，新父结点为v6<br>
7）3，7，正常连线，v7成为v3的父结点<br>
8）5，6，v5的父结点是v6，不能连线<br>
9）1，2，v1和v2的父节点都是v8，不能连线<br>
10）6，7，v6和v7分别是两个树的根结点，连接两个根结点生成新的树，v7成为新的根结点<br>
11）3，4，v3和v4的父节点都是v7，不能连线<br>
12）3，8，v3与v8的根结点都是v7，不能连线<br>
13）2，3，v2与v3的根结点都是v7，不能连线<br>
14）3，6，v3与v6的根结点都是v7，不能连线<br>
15）4，5，v4与v5的根结点都是v7，不能连线<br>

最终最小生成树的连接情况：<br>
![](https://img-blog.csdnimg.cn/20200603101833805.png)<br>
