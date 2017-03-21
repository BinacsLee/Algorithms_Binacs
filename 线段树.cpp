    
    
    
    #define maxn 100005
    
    int sum[maxn<<2],add[maxn<<2];//sum求和 add为lazy标记
    int A[maxn],n;//原数组
    
    void pushdown(int rt,int ln,int rn);//下传标记
    void pushup(int rt){            //PushUp函数更新节点信息 ，这里是求和
        sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    }
    void build(int l,int r,int rt){ //l,r表示当前节点区间，rt表示当前节点编号
        if(l==r){
            sum[rt]=A[l];return;
        }
        int m=(l+r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
        pushup(rt);
    }
    //点修改 update使A[L]+=C;
    void update(int L,int C,int l,int r,int rt){    //l,r表示当前节点区间，rt表示当前节点编号
        if(l==r){
            sum[rt]+=C;return;
        }
        int m=(l+r)>>1;
        if(L<=m) update(L,C,l,m,rt<<1);
        else update(L,C,m+1,r,rt<<1|1);
        pushup(rt);
    }
    //区间修改 假设A[L,R]+=C;
    void update(int L,int R,int C,int l,int r,int rt){
        if(L<=l&&r<=R){             //如果本区间完全在操作区间[L,R]以内
            sum[rt]+=C*(r-l+1);     //更新数字和，向上保持正确
            add[rt]+=C;     //增加Add标记，表示本区间的Sum正确，子区间的Sum仍需要根据Add的值来调整
           return;
        }
        int m=(l+r)>>1;
        pushdown(rt,m-1+1,r-m);     //下推标记
        //这里判断左右子树跟[L,R]有无交集，有交集才递归
        if(L<=m) update(L,R,C,l,m,rt<<1);
        if(R>m) update(L,R,C,m+1,R,rt<<1|1);
        pushup(rt);
    }
    //区间修改与查询 下面首先是下推标记的函数
    void pushdown(int rt,int ln,int rn){    //ln,rn为左子树，右子树的数字数量
        if(add[rt]){
            add[rt<<1]+=add[rt];
            add[rt<<1|1]+=add[rt];  //下推标记
            sum[rt<<1]+=add[rt]*ln;
            sum[rt<<1|1]+=add[rt]*rn;//修改子节点的Sum使之与对应的Add相对应
            add[rt]=0;
        }
    }
    //区间查询
    int query(int L,int R,int l,int r,int rt){  
        //L,R表示操作区间，l,r表示当前节点区间，rt表示当前节点编号
        if(L<=l&&r<=R) return sum[rt];
        int m=(l+r)>>1;
        pushdown(rt,m-l+1,r-m); //下推标记 否则sum可能不正确;
        
        int ans=0;        //累计答案
        if(L<=m) ans+=query(L,R,l,m,rt<<1);
        if(R>m) ans+=query(L,R,m+1,r,rt<<1|1);
        return ans;
    }
    
    
    

    
