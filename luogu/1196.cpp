#include <cstdio>
#include <algorithm>
using namespace std;
int fa[30005],order[30005],num[30005];
int find(int x)
{
 if(x==fa[x])return x;
 int a=find(fa[x]);
 order[x]+=order[fa[x]];
 return fa[x]=a;
}
void unionn(int x,int y)
{
 order[x]+=num[y];
 fa[x]=y;
 num[y]+=num[x];
 num[x]=0;
}
int main()
{
 int t;
 scanf("%d",&t);
 for(int i=1;i<=30000;i++)
  fa[i]=i,num[i]=1;
 for(int i=1;i<=t;i++)
 {
  int x,y;
  char op[5];
  scanf("%s%d%d",op,&x,&y);
  if(op[0]=='M')unionn(find(x),find(y));
  else
  {
   if(find(x)!=find(y))puts("-1");
   else printf("%d\n",abs(order[x]-order[y])-1);
  }
 }
 return 0;
}
