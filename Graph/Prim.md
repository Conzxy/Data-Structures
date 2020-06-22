# prim
prim是基于顶点来求得最小生成树。

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

## 实现代码
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;
int  const INF=65536;
string const alphabet("ABCDEFGHIJkLMNOPQRSTUVWXYZ");

char u,v;
int w;


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

void prim(vector<vector<int>> const&g,
  vector<int> &VT,vector<pair<int,int>> &ET)
{
  int numv=g.size();
  VT.push_back(0);
  vector<bool> lowcost(numv,false);
  lowcost[0]=true;
  for(int i=1;i<numv;i++)
  {
    int min=INF;
    int b=0,e=0;
    for(auto j=VT.begin();j!=VT.end();j++)
      for(int k=0;k<numv;k++)
      {
        if(g[*j][k]<min&&!lowcost[k])
        {
          min=g[*j][k];
          b=*j;
          e=k;
        }
      }
    lowcost[e]=true;
    VT.push_back(e);
    ET.push_back(make_pair(b,e));
  }
}

void prim1(vector<vector<int>> const&g,
  vector<int> &VT,vector<pair<int,int>> &ET)
  {
    int numv=g.size();
    VT.push_back(0);
    vector<int> lowcost;
    for(auto &x:g[0])
      lowcost.push_back(x);
    int b=0;
    for(int i=1;i<numv;i++)
    {
      int min=INF;
      int e=0;
      for(int k=0;k<numv;k++)
      {
        if(lowcost[k]<min&&lowcost[k])
          {
            min=lowcost[k];
            e=k;
          }
      }
      lowcost[e]=0;
      VT.push_back(e);
      ET.push_back(make_pair(b,e));

      for(int j=0;j<numv;j++)
        if(lowcost[j]&&g[e][j]<lowcost[j])
        {
          lowcost[j]=g[e][j];
          b=e;
        }
    }
  }
int main()
{
  int numv,nume;
  cin>>numv>>nume;
  vector<vector<int>> g(numv);
  vector<int> VT;
  vector<pair<int,int>> ET;

  getMatrix(g,numv,nume);
  prim1(g,VT,ET);
  //prim(g,VT,ET);

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

```
