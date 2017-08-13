/*    基础KMP P为模版串  *／
const int maxn=1e4+5;
char P[maxn];
char T[maxn];
int f[maxn];
void getFail(char* P,int *f){
    int m=strlen(P);
    f[0]=0;f[1]=0;
    for(int i=1;i<m;i++){
        int j=f[i];
        while(j&&P[i]!=P[j]) j=f[j];
        f[i+1]=P[i]==P[j]?j+1:0;
    }
}
void find(char* T,char* P,int* t){
    int n=strlen(T),m=strlen(P);
    getFail(P,f);
    int j=0;                            //当前节点编号 初始为0号节点
    for(int i=0;i<n;i++){               //文本串当前指针
        while(j&&P[j]!=T[i]) j=f[j];    //顺着失配边走 直到可以匹配
        if(P[j]==T[i]) j++;
        if(j==m) printf("%d\n",i-m+1);  //找到了 返回 可以改本函数返回类型
    }
}
