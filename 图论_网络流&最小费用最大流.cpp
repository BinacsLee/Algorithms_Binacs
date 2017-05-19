const int maxn=1005;
const int INF=0x3f3f3f3f;
struct Edge{
    int from,to,cap,flow;
};
int n,m;
struct Dinic{
    int n,m,s,t;
    vector<Edge> edges;//边表 edges[e]和edges[e^1]互为反向弧
    vector<int> G[maxn];//邻接表
    bool vis[maxn]; //bfs使用
    int d[maxn];    //起点到i的距离
    int cur[maxn];  //当前弧下标
    
    void init(int n){
        this->n=n;
        for(int i=0;i<=n;i++) G[i].clear();
        edges.clear();
    }
    
    void addedge(int from,int to,int cap){
        edges.push_back((Edge){from,to,cap,0});
        edges.push_back((Edge){to,from,0,0});
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    
    bool BFS(){
        memset(vis,0,sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s]=0;
        vis[s]=true;
        while(!Q.empty()){
            int x=Q.front();Q.pop();
            for(int i=0;i<G[x].size();i++){
                Edge& e=edges[G[x][i]];
                if(!vis[e.to]&&e.cap>e.flow){   //只考虑残量网络中的弧
                    vis[e.to]=true;
                    d[e.to]=d[x]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    
    int DFS(int x,int a){
        if(x==t||a==0) return a;
        int flow=0,f;
        for(int &i=cur[x];i<G[x].size();i++){   //从上次考虑的弧
            Edge& e=edges[G[x][i]];
            if(d[x]+1==d[e.to]&&(f=DFS(e.to,min(a,e.cap-e.flow)))>0){
                e.flow+=f;
                edges[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0) break;
            }
        }
        return flow;
    }
    
    int MaxFlow(int s,int t){
        this->s=s;this->t=t;
        int flow=0;
        while(BFS()){
            memset(cur,0,sizeof(cur));
            flow+=DFS(s,INF);
        }
        return flow;
    }
};
