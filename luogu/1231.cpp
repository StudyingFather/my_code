#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;
struct edge
{
 int v,w,next;
}e[200005];
int s,t,cnt=1;
int head[100005],dep[100005],vis[100005],cur[100005];
void addedge(int u,int v,int w)
{
 e[++cnt].v=v;
 e[cnt].w=w;
 e[cnt].next=head[u];
 head[u]=cnt;
}
bool bfs()
{
 queue<int> q;
 memset(dep,INF,sizeof(dep));
 memset(vis,0,sizeof(vis));
 memcpy(cur,head,sizeof(head));
 dep[s]=0;
 vis[s]=1;
 q.push(s);
 while(!q.empty())
 {
  int p=q.front();
  q.pop();
  vis[p]=0;
  for(int i=head[p];i;i=e[i].next)
   if(dep[e[i].v]>dep[p]+1&&e[i].w)
   {
    dep[e[i].v]=dep[p]+1;
    if(!vis[e[i].v])
    {
     vis[e[i].v]=1;
     q.push(e[i].v);
    }
   }
 }
 if(dep[t]==INF)return 0;
 return 1;
}
int dfs(int p,int w)
{
 if(p==t)return w;
 int used=0;
 for(int i=cur[p];i;i=e[i].next)
 {
  cur[p]=i;
  if(dep[e[i].v]==dep[p]+1&&e[i].w)
  {
   int flow=dfs(e[i].v,min(w-used,e[i].w));
   if(flow)
   {
    used+=flow;
    e[i].w-=flow;
    e[i^1].w+=flow;
    if(used==w)break;
   }
  }
 }
 return used;
}
int main()
{
 int n1,n2,n3,m1,m2;
 scanf("%d%d%d",&n1,&n2,&n3);
 scanf("%d",&m1);
 for(int i=1;i<=m1;i++)
 {
  int u,v;
  scanf("%d%d",&u,&v);
  addedge(v,n2+u,1);
  addedge(n2+u,v,0);
 }
 scanf("%d",&m2);
 for(int i=1;i<=m2;i++)
 {
  int u,v;
  scanf("%d%d",&u,&v);
  addedge(n1+n2+u,n1*2+n2+v,1);
  addedge(n1*2+n2+v,n1+n2+u,0);
 }
 for(int i=1;i<=n1;i++)
  addedge(n2+i,n1+n2+i,1),addedge(n1+n2+i,n2+i,0);
 t=n1*2+n2+n3+1;
 for(int i=1;i<=n2;i++)
  addedge(s,i,1),addedge(i,s,0);
 for(int i=1;i<=n3;i++)
  addedge(n1*2+n2+i,t,1),addedge(t,n1*2+n2+i,0);
 int ans=0;
 while(bfs())
  ans+=dfs(s,INF);
 printf("%d\n",ans);
 return 0;
}