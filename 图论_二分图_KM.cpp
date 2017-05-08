

/*------------------O(n^4)-------------------*/
const int maxn=1e4;
const int maxm=1e4;
int n,nx,ny;        //左右个数
int G[305][305];
int lx[maxn],ly[maxm];//顶标
bool visx[maxn],visy[maxm];
int link[maxm],slack[maxm];
bool dfs(int u){
    visx[u]=true;
    for(int i=1;i<=ny;i++)
        if(!visy[i]&&lx[u]+ly[i]==G[u][i]){
            visy[i]=true;
            if(!link[i]||dfs(link[i])){
                link[i]=u;return true;
            }
        }
    return false;
}
void update(){
    int d=1<<30;
    for(int i=1;i<=nx;i++) if(visx[i])
        for(int j=1;j<=ny;j++) if(!visy[j])
            d=min(d,lx[i]+ly[j]-G[i][j]);//if(d>lx[i]+ly[j]-G[i][j]) d=lx[i]+ly[j]-G[i][j];
    for(int i=1;i<=nx;i++) if(visx[i]) lx[i]-=d;
    for(int i=1;i<=ny;i++) if(visy[i]) ly[i]+=d;
}
int KM(){
    for(int i=1;i<=ny;i++){
        ly[i]=0;link[i]=0;  //注意link初始化0和-1细微区别
    }
    for(int i=1;i<=nx;i++){
        lx[i]=0;                // 若最小权
        for(int j=1;j<=ny;j++)
            if(G[i][j]>lx[i]) lx[i]=G[i][j];
    }
    
    for(int i=1;i<=nx;i++){
        for(;;){
            memset(visx,false,sizeof(visx));
            memset(visy,false,sizeof(visy));//for(int i=1;i<=ny;i++) visy[i]=false;
            if(dfs(i)) break;
            update();
        }
    }
    int res=0;
    for(int i=1;i<=ny;i++)
        if(link[i]) res+=G[link[i]][i];
    /*   检查未匹配
    for(int i=1;i<=ny;i++){
        if(link[i]) res+=G[link[i]][i];
        if(!link[i]||!G[link[i]][i]) return -1; //负权 if(!link[i]||W[link[i]][i]==-inf) return ?1?; 
    }
    */
    return res;
    
}
int main(){
    while(cin>>n){
        nx=ny=n;    // 最小权G初始化-INF
        for(int i=1;i<=nx;i++)
            for(int j=1;j<=ny;j++) scanf("%d",&G[i][j]);    //最小权则记录 G[i][j]=-d (d为输入的数据
        int res=KM();
        cout <<res<<endl; //  如过最小权 -res 取反
    }
    return 0;
}


/*---------------O(n^3)slack优化-----------------*/

const int INF=0x3f3f3f3f;
int slack[maxm];
bool dfs(int u){
    visx[u]=true;
    for(int i=1;i<=ny;i++){
        if(visy[i]) continue;
        int t=lx[u]+ly[i]-G[u][i];
        if(!t){
            visy[i]=true;
            if(!link[i]||dfs(link[i])){
                link[i]=u;return true;
            }
        }else if(t<slack[i]) slack[i]=t;
    }
    
    return false;
}
void update(){
    int d=1<<30;
    for(int i=1;i<=nx;i++)
        if(!visy[i]&&slack[i]<d) d=slack[i];    //attention
    for(int i=1;i<=nx;i++) if(visx[i]) lx[i]-=d;
    for(int i=1;i<=ny;i++) if(visy[i]) ly[i]+=d;else slack[i]-=d; //attention
}
int KM(){
    for(int i=1;i<=ny;i++){
        ly[i]=0;link[i]=0;/*slack[i]=0;*/
    }
    for(int i=1;i<=nx;i++){
        lx[i]=0;                // 若最小权
        for(int j=1;j<=ny;j++)
            if(G[i][j]>lx[i]) lx[i]=G[i][j];
    }
    
    for(int i=1;i<=nx;i++){
        for(int j=1;j<=ny;j++) slack[j]=INF;
        for(;;){
            memset(visx,false,sizeof(visx));
            memset(visy,false,sizeof(visy));//for(int i=1;i<=ny;i++) visy[i]=false;
            if(dfs(i)) break;
            update();
        }
    }
    int res=0;
    for(int i=1;i<=ny;i++)
        if(link[i]) res+=G[link[i]][i];
    return res;
    
}
int main(){
    while(cin>>n){
        nx=ny=n;    // 最小权G初始化-INF
        for(int i=1;i<=nx;i++)
            for(int j=1;j<=ny;j++) scanf("%d",&G[i][j]);    //最小权则记录 G[i][j]=-d (d为输入的数据
        int res=KM();
        cout <<res<<endl;
    }
    return 0;
}


