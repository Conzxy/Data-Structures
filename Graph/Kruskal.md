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
## 输入样本
10<br>
A B 14<br>
A F 13<br>
A E 22<br>
B F 12<br>
B C 21<br>
C F 18<br>
C D 16<br>
D E 20<br>
D F 19<br>
E F 24<br>

11<br>
A B 7<br>
A D 5<br>
B C 8<br>
B D 9<br>
B E 7<br>
C E 5<br>
D E 15<br>
D F 6<br>
E F 8<br>
E G 9<br>
F G 11<br>

0

## 输出样本
{BF,AF,CD,CF,DE}<br>
{AD,CE,DF,AB,BE,EG}
PS:0表示终止输入
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
## 时间复杂度
Tn=O(e)·O(sort)+O(e)·α(v)
α是阿克曼的反函数，近乎常数（不超过5）
因此Tn=O(eloge);
