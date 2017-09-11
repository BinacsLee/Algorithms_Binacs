typedef long long ll;
int n,k;
int a[100005];
int dp1[100005];
int dp2[100005];
int S[100005];
const int INF=0x3f3f3f3f;
int binary_search(int key, int *g, int low, int high){
    while (low < high)
    {
        int mid = (low + high) >> 1;
        if (key >= g[mid])
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}
int up(){
    memset(dp1,0,sizeof(dp1));
    dp1[1]=a[0];
    int len=1;    //初始化子序列长度为1，最小右边界
    int j=0;
    for (int i=1;i<n;i++){
        if(dp1[len]<=a[i])  //(如果允许子序列相邻元素相同 dp1[len]<=a[i],默认为不等）
            j=++len;        //a[i]>dp1[len],直接加入到dp1的末尾,且len++
        else j=binary_search(a[i],dp1,1,len+1);
        dp1[j]=a[i];        //二分查找,找到第一个比a[i]小的数dp1[k],并dp1[k+1]=a[i]
    }
    return len;
}

/////
void init(){
    for(int i=0;i<=n;i++) S[i]=-INF; //注意初始值
    memset(dp2,0,sizeof(dp2));
}
int BSearch(int x, int y, int v){
    while(x<=y){
        int mid = x+(y-x)/2;
        if(S[mid]>=v) x=mid+1; //注意看二分的变化
        else y = mid-1;
    }
    return x;
}
int down(){
    init();
    int ans=0;
    for(int i = 0; i <n; i++){
        int x=0,y=i;
        int pos=BSearch(x,y,a[i]);
        dp2[i] = pos;
        S[dp2[i]] = max(S[dp2[i]],a[i]); //max
        ans=max(ans,dp2[i]);
    }
    return ans+1;
}
