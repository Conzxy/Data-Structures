# prim
prim是基于顶点来求得最小生成树，因而适用于稠密图。

## 基本思想、
维护两个集合VT和ET，ET为所有已确定属于最小生成树的边，VT保存ET的所有边的端点，每一步都将距离VT“最近”但是不属于VT的顶点移入VT。

## 伪代码
```
1 VT←{v}，其中v为顶点集V的任意顶点（起始点），ET←∅
2 If  VT=V，则输出T={VT,ET}，
  Else
2.1 在集合E中选取权值最小的边uv，其中u∈VT，v∈V-VT
  （如存在多条，选一条即可）
2.2 VT←VT∪{v}，ET←ET∪{uv};
2.3 return step 2
```
## 输入样本
6 10<br>
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

7 11<br>
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

0 0

PS:0 0表示终止输入
## 输出样本
The minimal spanning tree's vertexes set:<br>
A F B C D E<br>
and its edges:<br>
(A,F) (F,B) (F,C) (C,D) (D,E)<br>

The minimal spanning tree's vertexes set:<br>
A D F B E C G<br>
and its edges:<br>
(A,D) (D,F) (A,B) (B,E) (E,C) (E,G)

## 实现代码
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;
int const INF=65536;
string const alphabet("ABCDEFGHIJkLMNOPQRSTUVWXYZ");  //字母与数字转换

char u,v;   //端点
int w;      //边权

//获得邻接矩阵
void getMatrix(vector<vector<int>> &g,int numv,int nume)  
{
  for(int i=0;i<numv;i++)
    for(int j=0;j<numv;j++)
    {
      if(i==j)
      g[i].push_back(0);
      else
      g[i].push_back(INF);
    }


  for(int i=0;i<nume;i++)
  {
      cin>>u>>v>>w;
      g[u-'A'][v-'A']=g[v-'A'][u-'A']=w;
  }
}

//prim——伪代码实现版本
void prim(vector<vector<int>> const&g,
  vector<int> &VT,vector<pair<int,int>> &ET)
{
  int numv=g.size();
  VT.push_back(0);
  vector<bool> final(numv,false);
  final[0]=true;
  for(int i=1;i<numv;i++)
  {
    int min=INF;
    int b=0,e=0;
    for(auto j=VT.begin();j!=VT.end();j++)
      for(int k=0;k<numv;k++)
      {
        if(!final[k]&&g[*j][k]<min)
        {
          min=g[*j][k];
          b=*j;
          e=k;
        }
      }
    final[e]=true;
    VT.push_back(e);
    ET.push_back(make_pair(b,e));
  }
}

//prim——lowcost存较小边权，adj存邻接点
void prim1(vector<vector<int>> const&g,
  vector<int> &VT,vector<pair<int,int>> &ET)
  {
    int numv=g.size();
    VT.push_back(0);
    vector<int> lowcost;
    vector<int> adj(numv,0);
    for(auto &x:g[0])
      lowcost.push_back(x);
    for(int i=1;i<numv;i++)
    {
      int min=INF;
      int e=0;
      for(int k=0;k<numv;k++)
      {
        if(lowcost[k]&&lowcost[k]<min)
          {
            min=lowcost[k];
            e=k;
          }
      }
      lowcost[e]=0;
      VT.push_back(e);
      ET.push_back(make_pair(adj[e],e));

      for(int j=0;j<numv;j++)
        if(lowcost[j]&&g[e][j]<lowcost[j])
        {
          lowcost[j]=g[e][j];
          adj[j]=e;
        }
    }
  }
int main()
{

  int numv,nume;
  while(cin>>numv>>nume&&numv>0&&nume>0){
    vector<vector<int>> g(numv);
    vector<int> VT;
    vector<pair<int,int>> ET;

    getMatrix(g,numv,nume);
    //prim1(g,VT,ET);
    prim(g,VT,ET);

    cout<<"The minimal spanning tree's vertexes set:"<<endl;
    for(auto &c:VT)
    {
      cout<<alphabet[c]<<" ";
    }
    cout<<endl;
    cout<<"and its edges:"<<endl;
    for(auto &x:ET)
    {
      cout<<"("<<alphabet[x.first]<<","<<alphabet[x.second]<<")"<<" ";
    }
  }
}
```
## 时间复杂度
### 第一个版本
最坏情况：<br>
![](https://img-blog.csdnimg.cn/20200622125907653.gif)<br>
最好情况：<br>
![](https://img-blog.csdnimg.cn/20200622125940172.gif)<br>
Tn=O(n^3),
主要是寻找最小边权花费了平方时间
### 第二个版本
这个版本优化了寻找最小边权，只需花费线性时间(空间换时间，但值得)
所以Tn=O(n^2)
