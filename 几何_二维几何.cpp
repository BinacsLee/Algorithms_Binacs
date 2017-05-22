
struct Point{
    double x,y;
    Point (double x=0,double y=0):x(x),y(y){}   // 构造函数
};
typedef Point Vector;

Vector operator + (Vector A,Vector B){ return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (Vector A,Vector B){ return Vector(A.x-B.x,A.y-B.y);}
Vector operator * (Vector A,double p){ return Vector(A.x*p,A.y*p);}
Vector operator / (Vector A,double p){ return Vector(A.x/p,A.y/p);}

bool operator < (const Point& a,const Point& b){
    return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
const double eps=1e-10;
int dcmp(double x){
    if(fabs(x)<eps) return 0;else return x<0?-1:1;
}
bool operator == (const Point& a,const Point& b){
    return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
}

/*-------- 基本运算 ----------*/
double Dot(Vector A,Vector B){ return A.x*B.x+A.y*B.y;}     //点积
double Length(Vector A){ return sqrt(Dot(A,A));}
double Angle(Vector A,Vector B){ return acos(Dot(A,B)/Length(A)/Length(B));}

double Cross(Vector A,Vector B){ return A.x*B.y-A.y*B.x;}       // 叉积
double Area2(Point A,Point B,Point C){ return Cross(B-A,C-A);}  // B与AC

Vector Rotate(Vector A,double rad){                         //向量旋转
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
Vector Normal(Vector A){            //计算向量的单位法线 (左转90 调用前需确认A不是零向量
    double L=Length(A);
    return Vector(-A.y/L,A.x/L);
}

/*-------- 点和直线 ----------*/
// 直线交点 P+tv (v=P'-P;向量)与Q+tw 调用前确保有交点(即Cross(v,w)!=0)  射线P+tv中t>0 线段0<t<1;
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w){
    Vector u=P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}
double DistanceToLine(Point P,Point A,Point B){     //利用叉积计算点到直线距离
    Vector v1=B-A,v2=P-A;
    return fabs(Cross(v1,v2))/Length(v1);   //如果不取绝对值 得到的是有向距离
}
double DistanceToSegment(Point P,Point A,Point B){  //点到线段距离
    if(A==B) return Length(P-A);
    Vector v1=B-A,v2=P-A,v3=P-B;
    if(dcmp(Dot(v1,v2))<0) return Length(v2);
    else if(dcmp(Dot(v1,v3))>0) return Length(v3);
    else return fabs(Cross(v1,v2))/Length(v1);
}
Point GetLineProjection(Point P,Point A,Point B){   //点P到直线AB投影
    Vector v=B-A;
    return A+v*(Dot(v,P-A)/Dot(v,v));
}
//下面线段相交判定 两线段恰好有一个公共点 且不在任何一条线段的端点
bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2){
    double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1),c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,b2-a1);
    return dcmp(c1)*dcmp(c2)<0&&dcmp(c3)*dcmp(c4)<0;
}
//如果允许端点处相交:若c1=c2==0两线段共线这时可能有部分重叠 若c1c2都不是0只有一种相交方法即某个端点在另一线段上
//为判断第二种端点情况 下列函数:
bool OnSegment(Point p,Point a1,Point a2){
    return dcmp(Cross(a1-p,a2-p))==0&&dcmp(Dot(a1-p,a2-p))<0;
}

/*-------- 多边形 ----------*/
double ConvexPolygonArea(Point* p,int n){   //对于凸多边形 分解成n-2个三角形
    double area=0;
    for(int i=1;i<n-1;i++)
        area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}
double PolygonArea(Point* p,int n){         //非凸多边形 正负抵消
    double area=0;
    for(int i=1;i<n-1;i++)
        area+=Cross(p[i]-p[0],p[i+1]-p[0]);
    return area/2;
}

