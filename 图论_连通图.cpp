





/*-----------------------tarjan(poj1236)-----------------------*/

const int maxn=105;
int n;
vector<int> G[maxn];
int pre[maxn],lowlink[maxn],sccno[maxn],dfs_clock,scc_cnt;
stack<int> s;
int in[maxn],out[maxn];   //锁点后统计

void dfs(int u){
    pre[u]=lowlink[u]=++dfs_clock;
    s.push(u);
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(!pre[v]){
            dfs(v);
            lowlink[u]=min(lowlink[u],lowlink[v]);
        }else if(!sccno[v]){
            lowlink[u]=min(lowlink[u],lowlink[v]);
        }
    }
    if(lowlink[u]==pre[u]){
        scc_cnt++;
        for(;;){
            int x=s.top();s.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
}
void find_scc(){
    dfs_clock=scc_cnt=0;
    memset(sccno,0,sizeof(sccno));
    memset(pre,0,sizeof(pre));
    for(int i=0;i<n;i++)
        if(!pre[i]) dfs(i);
}
int main(){
    while(cin>>n){
        int v;
        for(int i=0;i<n;i++){
            //cout <<i<<endl;
            G[i].clear();
            while(cin>>v&&v) G[i].push_back(--v);
        }
        find_scc();
        
        if(scc_cnt==1) {cout <<1<<endl<<0<<endl;continue;}
        
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        for (int u=0;u<n;u++){
            for (int i=0;i<G[u].size();i++){
                int v=G[u][i];
                if(sccno[u]!=sccno[v])               // 强连通分量算一个点
                    ++out[sccno[u]], ++in[sccno[v]];
            }
        }
        int zero_in=0,zero_out=0;
        for(int i=1;i<=scc_cnt;i++){
            if(in[i]==0) zero_in++;
            if(out[i]==0) zero_out++;
        }
        cout <<zero_in<<endl;
        cout <<max(zero_in,zero_out)<<endl;
    }
    return 0;
}

