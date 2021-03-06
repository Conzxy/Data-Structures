#include "Matrix.h"
using namespace std;
bool flag=true;
const int maxs = 1e6+5;
int fa[maxs], degree[maxs];
set<int> s;
set<int>::iterator it;


void addedge_non_direct(vector<ipair> *adj,int u,int v,int wt)
{
    adj[u].push_back(make_pair(v,wt));
    adj[v].push_back(make_pair(u,wt));
}

void addedge_direct(vector<ipair> *adj,int u,int v,int wt)
{
    adj[u].push_back(make_pair(v,wt));
}

int edge_count(vector<vector<int>> const&g,int direct)
{
    int cnt=0;
    if(direct==0)
    {
        for(int i=0;i<g.size();i++)
            for(int j=i+1;j<g.size();j++)
                if(g[i][j]!=INIF)
                    cnt++;
    }
    else
    {
        for(int i=0;i<g.size();i++)
            for(int j=0;j<g.size();j++)
                if(g[i][j]!=0&&g[i][j]!=INIF)
                    cnt++;
    }
    return cnt;

}

void getMatrix(vector<vector<int>> &g,int numv,int nume,int direct)
{
    for(int i=0;i<numv;i++)
        for(int j=0;j<numv;j++)
        {
            if(i==j)
                g[i].push_back(0);
            else
                g[i].push_back(INIF);
        }
    for(int i=0;i<nume;i++)
    {
        int u,v;
        cin>>u>>v;
        if(direct==1)
            g[u-1][v-1]=1;
        else
            g[u-1][v-1]=g[v-1][u-1]=1;
    }

}

void solve1()
{
    int numv,nume,direct;
    cin>>numv>>nume>>direct;

    vector<vector<int>> g(numv);
    getMatrix(g,numv,nume,direct);

    int edgecnt=edge_count(g,direct);
    cout<<edgecnt;
}

void Dijkstra(vector<vector<int>> const&g,vector<int> &d,int numv,int v)
{
    int min,k=0;
    vector<bool> final(numv,false);
    final[v]=true;
    d[v]=0;
    for(int i=0;i<numv;i++)
        d[i]=g[v][i];
    for(int i=0;i<numv;i++)
    {
        min=INIF;
        for(int j=0;j<numv;j++)
        {
            if(!final[j]&&d[j]<min)
            {
                min=d[j];
                k=j;
            }
        }
        final[k]=true;
        for(int w=0;w<numv;w++)
        {
            if(!final[w]&&min+g[k][w]<d[w])
            {
                d[w]=min+g[k][w];
                //p[w]=k;
            }
        }
    }
}

void Dijkstra_heap(vector<ipair> *adj,int numv,int v)
{
    priority_queue<ipair,vector<ipair>,greater<ipair>> pq;
    //优先队列，按great排序可以构造小根堆，ipair将依次比较first，second
    vector<int> dist(numv,INIF);            //将其他点权置为无穷大
    dist[v]=0;                              //源点点权置为0
    //vector<bool> final(numv,false);       //若顶点比较少，实在没必要
    pq.push(make_pair(0,v));                //将源点放在堆顶
    //pq.push(make_pair(dist[v],v));


    while(!pq.empty())
    {
      int u=pq.top().second;                //取当前最小点权值对应的顶点
      pq.pop();

      for(auto x:adj[u])                    //adj[u]的first保存u邻接边的另一端，second保存边权
      {
        //if(!final[u]){
          int s=x.first;                    //邻接边的另一端
          int weight=x.second;              //邻接边的边权
          if(dist[u]+weight<dist[s])        //可以松弛
          {
            //松弛操作
            dist[s]=dist[u]+weight;
            pq.push(make_pair(dist[s],s));
          }
      //}
      }
      //final[u]=true;                      //表示该点的邻接边已经全部访问了并防止吃回头草
    }
    for(int i=0;i<numv;i++)
    {
        if(dist[i]==INIF)
        {
          dist[i]=-1;                       //置为-1表示不存在到该顶点的最短路径
        }
        cout<<dist[i]<<" ";                 //输出源点到每个顶点的最短路径
    }
}

void solve21()
{
    int numv,nume,direct;
    cin>>numv>>nume>>direct;

    vector<vector<int>> g(numv);
    getMatrix(g,numv,nume,direct);

    int s;
    cin>>s;

    vector<int> d(numv);
    Dijkstra(g,d,numv,s-1);


    for(auto &x:d)
    {
        cout<<((x==INIF)?-1:x)<<" ";                 //输出源点到每个顶点的最短路径
    }
}

void solve22()
{
    int numv,nume,direct,u,v,s;
    cin>>numv>>nume>>direct;//顶点数，边数，有向依据
    vector<ipair> adj[numv];
    for(int i=0;i<nume;i++)
    {
        cin>>u>>v;  //边头部和尾部
        if(direct==0){
            addedge_non_direct(adj,u-1,v-1);  //无权将边权置为1来表示边数，若有权则覆盖默认实参
        }
        else
        {
            addedge_direct(adj,u-1,v-1);
        }
    }
    cin>>s;     //源点
    Dijkstra_heap(adj, numv, s-1);
}

int Find(int x)
{
    return fa[x]==x?x:(fa[x]=Find(fa[x]));
}

void Union(int u,int v)
{
    int x=Find(u);
    int y=Find(v);
    if(x==y)
        flag=false;
    else
        fa[y]=x;
}

void init()
{
    for(int i=0;i<maxs;i++)
    {
        fa[i]=i;
        degree[i]=0;
    }
}

bool root_check()
{
    it=s.begin();
    int root=Find(fa[*it]);
    for(;it!=s.end();it++)
    {
        int t=Find(fa[*it]);
        if(t!=root)
        {
            flag=false;
            return false;
        }
    }
    return true;
}

void degree_check()
{
    if(root_check())
    {
        set<int>::iterator it=s.begin();
        int root=Find(fa[*it]);
        if(degree[root]!=0)
        {
            flag=false;
            return ;
        }
        for(;it!=s.end();it++)
        {
            int t=*it;
            if(t!=root&&degree[t]!=1)
            {
                flag=false;
                return ;
            }
        }
    }
}

void check()
{
    degree_check();
}

void solve3()
{
    int numv,nume,direct;
    cin>>numv>>nume>>direct;
    if(direct==0) return;
    init();
    int u,v;
    for(int i=0;i<nume;i++)
    {
        cin>>u>>v;
        Union(u,v);
        s.insert(u);
        s.insert(v);
        degree[v]++;
    }
    if(flag==true) check();
    cout<<((flag==true)?"TRUE":"FALSE");
}

void DFSTravel(int numv,vector<vector<int>> const&g,int u)
{
    vector<bool> visited(numv,false);

    DFS(u,visited,g);

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

void solve4()
{
    int numv,nume,direct,u;
    cin>>numv>>nume>>direct;

    vector<vector<int>>g(numv);
    getMatrix(g,numv,nume,direct);

    cin>>u;
    DFSTravel(numv,g,u-1);
}
