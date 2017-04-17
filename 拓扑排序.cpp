
int c[maxn];
int topo[maxn],t;
bool G[maxn][maxn];

bool dfs(int u){
  c[u]=-1;//访问标志
  for(int v=1;v<=n;v++) if(G[u][v]) {
    if(c[v]<0) return false;  //有向环 退出
    else if(!c[v]&&!dfs(v)) return false;
  }
  c[u]=1;topo[t--]=u;
  return true;
}

bool toposort(){
  t=n;
  memset(c,0,sizeof(c));
  for(int u=1;u<=n;u++) if(!c[u])
    if(!dfs(u)) return false;
  return true;
}


