#include <iostream>
#include <map>
#include <stack>
#include <set>
#include <string>
#include <sstream>
#include <cstring>
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int color[205];
int link[205],n,m;
bool vis[205];
vector<int> e[205];

bool judge(int x){
    int len=e[x].size();
    for(int i=0;i<len;i++){
        int y=e[x][i];
        if(color[y]==-1){
            color[y]=(color[x]^1);
            if(!judge(y)) return false;
        }else if(color[y]==color[x]) return false;
    }
    return true;
}
bool dfs(int x){
    int len=e[x].size();
    for(int i=0;i<len;i++){
        int y=e[x][i];
        if(!vis[y]){
            vis[y]=true;
            if(link[y]==-1||dfs(link[y])){
                link[y]=x;return true;
            }
        }
    }
    return false;
}

int main(){
    while(cin>>n>>m){
        for(int i=0;i<=n;i++) e[i].clear();
        int u,v;
        while(m--){
            scanf("%d%d",&u,&v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        memset(color,-1,sizeof(color));
        bool suc=true;
        for(int i=1;i<=n;i++){
            if(color[i]==-1){
                color[i]=0;
                if(!judge(i)){
                    suc=false;break;
                }
            }
        }
        if(!suc) { cout <<"No\n";continue;}
        
        //
        int ans=0;
        memset(link,-1,sizeof(link));
        for(int i=1;i<=n;i++){
            if(color[i]==0){
                memset(vis,false,sizeof(vis));
                if(dfs(i)) ans++;
            }
        }
        cout <<ans<<endl;
        //
    }
    return 0;
}


／*----------多重匹配-----------*／
int vlink[m],link[n][m];
bool dfs(int x){
    for(int i=0;i<m;i++){
        if(!vis[i]&&G[x][i]){
            vis[i]=true;
            if(vlink[i]<maxcap){
                link[i][vlink[i]++]=x;return true;
            }
            for(int j=0;j<vlink[i];j++){
                if(dfs(link[i][j])){
                    link[i][j]=x;return true;
                }
            }
        }
    }
    return false;
}
