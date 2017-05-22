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

double Dot(Vector A,Vector B){ return A.x*B.x+A.y*B.y;}     //点积
double Length(Vector A){ return sqrt(Dot(A,A));}
Vector Rotate(Vector A,double rad){                         //向量旋转
    return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
//////////////////////////////
const double PI=3.1415926;
struct Circle{
    Point c;
    double r;
    Circle (Point c,double r):c(c),r(r){}
    Point point(double a){
        return Point(c.x+cos(a)*r,c.y+sin(a)*r);
    }
};
struct Line{    //这个书上缺了..
    Point p;
    Vector v;
    Point point(int t){
        return Point(p.x+v.x*t,p.y+v.y*t);
    }
};
int getLineCircleIntersection(Line L,Circle C,double& t1,double& t2,vector<Point>& sol){
    double a=L.v.x,b=L.p.x-C.c.x,c=L.v.y,d=L.p.y-C.c.y;
    double e=a*a+c*c,f=2*(a*b+c*d),g=b*b+d*d-C.r*C.r;
    double delta=f*f-4*e*g;
    if(dcmp(delta)<0) return 0; //相离
    else if(dcmp(delta)==0){
        t1=t2=-f/(2*e);sol.push_back(L.point(t1));
        return 1;           //相切
    }
    //  相交
    t1=(-f-sqrt(delta))/(2*e);sol.push_back(L.point(t1));
    t2=(-f+sqrt(delta))/(2*e);sol.push_back(L.point(t2));
    return 2;
}
//  园与圆的关系
double angel(Vector v){ return atan2(v.y,v.x);} //计算向量极角
int getCircleCircleIntersection(Circle C1,Circle C2,vector<Point>& sol){    //圆与圆的关系
    double d=Length(C1.c-C2.c);
    if(dcmp(d)==0){
        if(dcmp(C1.r-C2.r)==0) return -1;   //两圆重合
        return 0;
    }
    if(dcmp(C1.r+C2.r-d)<0) return 0;
    if(dcmp(fabs(C1.r-C2.r)-d)>0) return 0;
    
    double a=angel(C2.c-C1.c);  //向量C1C2的极角
    double da=acos((C1.r*C1.r+d*d-C2.r*C2.r))/(2*C1.r*d);//C1C2到C1P1的角
    Point p1=C1.point(a-da),p2=C1.point(a+da);
    
    sol.push_back(p1);
    if(p1==p2) return 1;
    sol.push_back(p2);
    return 2;
}
// 过点p到圆C的切线 返回切线条数 v数组存第i条切线的向量
int getTangents(Point p,Circle C,Vector* v){
    Vector u=C.c-p;
    double dist=Length(u);
    if(dist<C.r) return 0;
    else if(dcmp(dist-C.r)==0){
        v[0]=Rotate(u,PI/2);return 1;
    }else{
        double ang=asin(C.r/dist);
        v[0]=Rotate(u,-ang);
        v[1]=Rotate(u,+ang);
        return 2;
    }
}
//  求两圆的公切线
//  1.两圆完全重合 有无数条公切线
//  2.两圆内含 没有公共点 没有公切线
//  3.两圆内切 1条公切线
//  4.两圆相交 2条外公切线
//  5.两圆外切 3条公切线
//  6.两圆相离 4条公切线
//      返回切线条数 -1表示无穷条  a[i] b[i]分别是第i条切线在圆A B上的切点
int getTangents(Circle A,Circle B,Point* a,Point* b){
    int cnt=0;
    if(A.r<B.r){swap(A,B);swap(a,b);}
    int d2=(A.c.x-B.c.x)*(A.c.x-B.c.x)+(A.c.y-B.c.y)*(A.c.y-B.c.y);
    int rdiff=A.r-B.r;
    int rsum=A.r+B.r;
    if(d2<rdiff*rdiff) return 0;    //内含
    
    double base=atan2(B.c.y-A.c.y,B.c.x-A.c.x);
    if(d2==0&&A.r==B.r) return -1;  //无穷多条切线
    if(d2==rdiff*rdiff){
        // !!!!  warning
        a[cnt]=A.getPoint(base);b[cnt]=B.getPoint(base);cnt++;  //书上缺getPoint函数 !!!!
        // !!!!  warning
        return 1;
    }
    //有外公切线
    double ang=acos((A.r-B.r)/sqrt(d2));
    a[cnt]=A.getPoint(base+ang);b[cnt]=B.getPoint(base+ang);cnt++;
    a[cnt]=A.getPoint(base-ang);b[cnt]=B.getPoint(base-ang);cnt++;
    if(d2==rsum*rsum){  //一条内公切线
        a[cnt]=A.getPoint(base);b[cnt]=B.getPoint(PI+base);cnt++;
    }else if(d2>rsum*rsum){
        double ang=acos((A.r+B.r)/sqrt(d2));
        a[cnt]=A.getPoint(base+ang);b[cnt]=B.getPoint(PI+base+ang);cnt++;
        a[cnt]=A.getPoint(base-ang);b[cnt]=B.getPoint(PI+base-ang);cnt++;
    }
    return cnt;
}

//todo
