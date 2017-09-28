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

/*    manacher     */
char ma[1000005],s[500005];
void manacher(int len){
    int l=0;
    ma[l++]='$';
    ma[l++]='#';
    for(int i=0;i<len;i++){
        ma[l++]=s[i];
        ma[l++]='#';
    }
    ma[l]=0;
    int mx=0,id=0;
    for(int i=0;i<l;i++){
        mp[i]=mx>i?min(mp[2*id-i],mx-i):1;
        while(ma[i+mp[i]]==ma[i-mp[i]]) mp[i]++;
        if(i+mp[i]>mx){
            mx=i+mp[i];
            id=i;
        }
    }
}
//
//        abcde->%a%b%c%d%e% 
//        记录p[i]表示i能向两边推（包括i）的最大距离，如果能求出p，则答案就是max(p)-1了
//        （以i为中点的最长回文为2*p[i]-1，但这是加过字符后的答案，把加进去的字符干掉，最长回文就是p[i]-1

