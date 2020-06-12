# 深度优先遍历
深度优先遍历，简称DFS，是一种图的遍历方式，特点是**不撞南墙不回头**

## 实现代码
```cpp
void DFSTravel(int numv,vector<vector<int>> const&g,int u)
{
    vector<bool> visited(numv,false);

    DFS(u,visited,g); //若是连通图，只执行这步

    for(int i=0;i<numv;i++)
        if(!visited[i])
            DFS(i,visited,g);
}

void DFS(int v,vector<bool>& visited,vector<vector<int>> const& g)
{
      visited[v]=true;
      cout<<v+1<<" ";
      for(int i=0;i<g.size();i++)
        if(g[v][i]!=INIF&&g[v][i]!=0&&!visited[i])
          DFS(i,visited,g);
}
```

## 测试代码
```cpp
int main()
{
    int numv,nume,direct,u;
    cin>>numv>>nume>>direct;

    vector<vector<int>>g(numv);
    getMatrix(g,numv,nume,direct);

    cin>>u;
    DFSTravel(numv,g,u-1);

    return 0;
}
```
