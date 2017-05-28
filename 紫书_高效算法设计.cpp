

/*------------------------------------------------------------------------------------------------*/

// 归并排序 A愿数组 T临时数组
void merge_sort(int* A,int x,int y,int* T){
    if(y-x>1){              //attention
        int m=x+(y-x)/2;    //attention
        int p=x,q=m,i=x;
        merge_sort(A,x,m,T);
        merge_sort(A,m,y,T);
        while(p<m||q<y){
            if(q>=y||(p<m&&A[p]<=A[q])) T[i++]=A[p++];  //从左半数组复制到临时空间
            else T[i++]=A[q++];                         //从右半数组复制到临时空间
        }
        for(int i=x;i<y;i++) A[i]=T[i];     // attention i<y 与if中 q>=y 以及首行 y-x>1 相应
    }
}

//利用归并排序统计逆序对 也即冒泡排序交换次数 (输入数据个数可能很多so统计逆序对咯
int cnt=0;  //init
void func(int* A,int x,int y,int* T){
    if(y-x>1){
        int m=x+(y-x)/2;
        int p=x,q=m,i=x;
        merge_sort(A,x,m,T);
        merge_sort(A,m,y,T);
        while(p<m||q<y){
            if(q>=y||(p<m&&A[p]<=A[q])) T[i++]=A[p++];
            else {T[i++]=A[q++];cnt+=m-p;}  //attention
        }
        for(int i=x;i<y;i++) A[i]=T[i];
    }
}

/*------------------------------------------------------------------------------------------------*/
