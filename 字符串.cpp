/*    基础KMP P为模版串  */
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
        if(j==m){
            printf("%d\n",i-m+1);  //找到了 返回 可以改本函数返回类型
            j=0; //  若不可重叠匹配
            j=f[j]; //若可重叠匹配
        }
    }
}


/*    拓展KMP P为模版串  */
int nt[100005],ex[100005];
char T[100005],P[100005];
void get_next(char* P,int* nt){
    int m=strlen(P),a=0;
    nt[0]=m;
    while(a<m-1&&P[a]==P[a+1]) a++;
    nt[1]=a;
    a=1;
    for(int i=2;i<m;i++){
        int p=a+nt[a]-1,l=nt[i-a];
        if((i-1)+l>=p){
            int j=(p-i+1)>0?(p-i+1):0;
            while(i+j<m&&P[i+j]==T[j]) j++;
            nt[i]=j;
            a=i;
        }else nt[i]=l;
    }
}

void exkmp(char* T,char* P,int *nt){
    get_next(P,nt);
    int n=strlen(T),m=strlen(P),a=0;
    int minl=n<m?n:m;
    while(a<minl&&T[a]==P[a]) a++;
    ex[0]=a;
    a=0;
    for(int i=1;i<minl;i++){
        int p=a+ex[a]-1,l=nt[i-a];
        if((i-1)+l>=p){
            int j=(p-i+1)>0?(p-i+1):0;
            while(i+j<n&&j<m&&T[i+j]==P[j]) j++;
            ex[i]=j;
            a=i;
        }else ex[i]=l;
    }
}
