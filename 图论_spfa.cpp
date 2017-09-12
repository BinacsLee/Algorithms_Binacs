const int maxn=10005;
const int INF=0x3f3f3f3f;
int n,m,k;
struct node{
    int x,y;
}nos[maxn];
int d[maxn],inq[maxn];//是否在操作队列中
int spfa(){
    queue<int> q;
    for(int i=1;i<=k;i++) d[i]=INF;
    d[1]=0;
    inq[1]=1;
    q.push(1);
    while(!q.empty()){
        int e=q.front();q.pop();
        for(int i=1;i<=k;i++) if(i!=e){
            int x=abs(nos[i].x-nos[e].x),y=abs(nos[i].y-nos[e].y);
            int v=INF;
            if(x+y==1) v=0;
            else if(x<=2||y<=2) v=1;
            if(d[i]>d[e]+v){
                d[i]=d[e]+v;
                if(!inq[i]){ inq[i]=1;q.push(i);}
            }
        }
        inq[e]=0;
    }
    return d[k]==INF?-1:d[k];
}
int main(){
    cin>>n>>m>>k;
    bool flag=false;
    for(int i=1;i<=k;i++){
        scanf("%d%d",&nos[i].x,&nos[i].y);
        if(nos[i].x==n&&nos[i].y==m) flag=true;
    }
    if(!flag) {nos[++k].x=n+1;nos[k].y=m+1;}    //若没亮加上
    cout<<spfa()<<endl;
    return 0;
}
