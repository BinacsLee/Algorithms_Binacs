
int A[100],T[100];
void merge_sort(int* A,int x,int y,int* T){
    if(y-x>1){
        int m=x+(y-x)/2;        //划分
        int p=x,q=m,i=x;
        merge_sort(A,x,m,T);
        merge_sort(A,m,y,T);
        while(p<m||q<y){
            if(q>=y||(p<m&&A[p]<=A[q])){
                T[i++]=A[p++];  //从作伴数组复制到临时空间
                
            }else{
                T[i++]=A[q++];
                //cnt+=m-p;     如果需要统计逆序对
            }
        }
        for(int i=x;i<y;i++) A[i]=T[i];
    }
}

int main(){
    int n;
    while(cin>>n){
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        // int cnt=0;
        merge_sort(A,1,n+1,T);  //attention 是1到n+1
        
        // printf("%d\n",cnt);
        for(int i=1;i<=n;i++) printf("%d ",A[i]);
        printf("\n");
    }
    return 0;
}
