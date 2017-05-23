
typedef long long LL;

LL gcd(LL a,LL b){
    return b==0?a:gcd(b,a%b);
}
//  求整数x y 使得ax+by=d且|x|+|y|最小 其中d=gcd(a,b)
void gcd(LL a,LL b,LL& d,LL& x,LL& y){
    if(!b){ d=a;x=1;y=0;}
    else{ gcd(b,a%b,d,y,x);y-=x*(a/b);}
}
//  计算模n下a的逆 若不存在返回-1
LL inv(LL a,LL n){
    LL d,x,y;
    gcd(a,n,d,x,y);
    return d==1?(x+n)%n:-1;
}

// 欧拉函数相关
int euler_phi(int n){
    int m=(int)sqrt(n+0.5);
    int ans=n;
    for(int i=2;i<=m;i++) if(n%i==0){
        ans=ans/i*(i-1);
        while(n%i==0) n/=i;
    }
    if(n>1) ans=ans/n*(n-1);
    return ans;     //返回phi(n)
}
int phi[maxn];
void phi_table(int n){
    for(int i=2;i<=n;i++) phi[i]=0;
    phi[1]=1;
    for(int i=2;i<=n;i++) if(!phi[i]){
        for(int j=i;j<=n;j+=i){
            if(!phi[j]) phi[j]=j;
            phi[j]=phi[j]/i*(i-1);
        }
    }
}

// china remainder theorem
// n个方程: x=a[i](mod m[i]) (0<=i<n)
LL a[maxn],m[maxn];
LL china(int n,int* a,int *m){
    LL M=1,d,y,x=0;
    for(int i=0;i<n;i++) M*=m[i];
    for(int i=0;i<n;i++){
        LL w=M/m[i];
        gcd(m[i],w,d,d,y);
        x=(x+y*w*a[i])%M;
    }
    return (x+M)%M;
}

//
LL pow_mod(LL x,LL n,LL mod){
    LL res=1;
    while(n>0){
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
// 离散对数 考虑 a^x===b(mod n) n为素数  则只要a不等于0即存在逆a^-1
//  求解上述模方程 n为素数 无解返回-1
int log_mod(int a,int b,int n){
    int m,v,e=1;
    m=(int)sqrt(n+0.5);
    v=inv(pow_mod(a,m,n),n);
    map<int,int> x;
    x[1]=0;
    for(int i=1;i<m;i++){   //计算e[i]
        //e=mul_mod(e,a,n);
        e=e*a%n;
        if(!x.count(e)) x[e]=i;
    }
    for(int i=0;i<m;i++){   //考虑 a^(im),a^(im+1),...,a^(im+m-1)
        if(x.count(b)) return i*m+x[b];
        //b=mul_mod(b,v,n);
        b=b*v%n;
    }
    return -1;
}
