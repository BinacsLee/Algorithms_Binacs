typedef long long ll;

ll mod_pow(ll x,ll n,ll mod){
    ll res=1;
    while(n>0){
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}

/*---------- 矩阵快速幂 -----------*/
struct matrix{
    int m[2][2];
};
const int mod=10000;
matrix multiply(matrix x,matrix y){
    matrix tem;
    memset(tem.m,0,sizeof(tem.m));
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++)
                tem.m[i][j]+=((x.m[i][k]*y.m[k][j])%mod+mod)%mod;
    return tem;
}
matrix mod_pow(matrix P,ll n){
    matrix res;
    memset(res.m,0,sizeof(res.m));
    res.m[0][0]=res.m[1][1]=1;
    while(n){
        if(n&1) res=multiply(res,P);
        P=multiply(P,P);
        n>>=1;
    }
    return res;
}

// 注意mod 即便是最后输出的
