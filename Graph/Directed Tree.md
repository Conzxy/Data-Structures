# 判断有向树
## 有向树的特征
* 根的入度为0，其他均为1
* 不能成环
* 只能有一个根

## 思路
用并查集来解决该问题是最好的。<br>
* init 初始化
* Union 合并操作(包含成环判断)
* Find 查找操作
* 唯一根结点检查 root_check
* 入度检查 degree_check

## 实现代码
```cpp
bool flag=true;             //有向树标志
const int maxs = 1e6+5;   
int fa[maxs], degree[maxs]; //全局数组
set<int> s;
set<int>::iterator it;

int Find(int x)         //寻找父节点   
{
    return fa[x]==x?x:(fa[x]=Find(fa[x]));
    //路径压缩优化
}

void Union(int u,int v)   //合并
{
    int x=Find(u);
    int y=Find(v);
    if(x==y)
        flag=false; //成环了
    else
        fa[y]=x;
}

void init()           //初始化
{
    for(int i=0;i<maxs;i++)
    {
        fa[i]=i;
        degree[i]=0;  
    }
}

bool root_check()     //检查唯一根结点
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

void degree_check()     //检查入度
{
    if(root_check())
    {
        it=s.begin();
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
```
## 测试代码
```cpp
int main()
{
    int numv,nume,direct;   //numv无用，只是为了格式
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
```
