# Kruskal
kruskal与prim不同，是基于边去构造最小生成树，所以适用于边比较少的稀疏图。<br>
kruskal需要边的集合，我们称其为边集数组。边集数组按从小到大的顺序排序，方便构造最小生成树。<br>
## 边集数组
结构体
```cpp
struct edge {
    int begin, end, weight;
    bool operator<(edge const& rhs)
    {return this->weight < rhs.weight;}
}edges[maxsize * (maxsize - 1)];
```
边集数组构造函数
```cpp
void get_edges_set()
{
    int a = 0;
    for (int i = 0; i < nume; i++)
    {
        cin >> u >> v >> w;
        edges[a].begin = u - 'A';
        edges[a].end = v - 'A';
        edges[a++].weight = w;
    }
    sort(edges, edges + a);
}
```

## 构造最小生成树
边集数组构造好，vector中根据权值从小到大排序。我们沿着下标选择begin和end连线来构造最小生成树，但是，在连接过程中可能出现成环的现象，这是由于父节点重复了，孩子想与父节点连在一起或是孩子想连在一起而造成的一种严重错误。<br>
我们可以通过并查集来避开成环情况。
```cpp
int findset(int x)
{
    return (fa[x] == x) ? x : findset(fa[x]);
}

void Union(int b, int e)
{
    int bb = findset(b);
    int ee = findset(e);
    if (bb != ee)
        fa[bb] = ee;
}

void init()
{
    for(int i = 0; i < maxsize; i++)
        fa[i] = i;
}
```
Kruskal
```cpp
void kruskal(vector<pair<int, int>>& ET)
{
    for (int i = 0; i < nume; i++)
    {
        int uu = findset(edges[i].begin);
        int vv = findset(edges[i].end);
        if (uu != vv)
        {
            Union(edges[i].begin, edges[i].end);
            ET.push_back(make_pair(edges[i].begin, edges[i].end));
        }
    }
}
```
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

## 实现代码
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
string const alphabet("ABCDEFGHIJkLMNOPQRSTUVWXYZ");
int const maxsize = 26;
int fa[maxsize];
int nume, w;
char u, v;
struct edge {
    int begin, end, weight;
    bool operator<(edge const& rhs)
    {
        return this->weight < rhs.weight;
    }
}edges[maxsize * (maxsize - 1)];

void get_edges_set()
{
    int a = 0;
    for (int i = 0; i < nume; i++)
    {
        cin >> u >> v >> w;
        edges[a].begin = u - 'A';
        edges[a].end = v - 'A';
        edges[a++].weight = w;
    }
    sort(edges, edges + a);
}

int findset(int x)
{
    return (fa[x] == x) ? x : findset(fa[x]);
}

void Union(int b, int e)
{
    int bb = findset(b);
    int ee = findset(e);
    if (bb != ee)
        fa[bb] = ee;
}

void init()
{
    for(int i = 0; i < maxsize; i++)
        fa[i] = i;
}
void kruskal(vector<pair<int, int>>& ET)
{
    for (int i = 0; i < nume; i++)
    {
        int uu = findset(edges[i].begin);
        int vv = findset(edges[i].end);
        if (uu != vv)
        {
            Union(edges[i].begin, edges[i].end);
            ET.push_back(make_pair(edges[i].begin, edges[i].end));
        }
    }
}

int main()
{
    while (cin >> nume && nume > 0)
    {
        init();
        vector<pair<int, int>> ET;
        get_edges_set();
        kruskal(ET);

        cout << "{";
        for (auto i=ET.begin();i!=ET.end();i++)
        {
            if(i!=prev(ET.end()))
            cout << alphabet[(*i).first] << alphabet[(*i).second] << ",";
            else
            cout << alphabet[(*i).first] << alphabet[(*i).second] ;
        }
        cout << "}";
    }
}

```
