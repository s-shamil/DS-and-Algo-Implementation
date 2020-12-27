/*
Solvw using Divide and Conquer.
Closest pair of points: 
You are given n points in the plane (i.e. two dimensions). 
Provide a divide and conquer algorithm to determine pair of points that are closest to each other in time O(n log n)
(Reference: Kleinberg & Tardos – Section 5.4).
Input:
First line of the input file will contain the number of points, n followed by two numbers per line (may not be integers) giving co-ordinates of the points. For example:
5
0 0
-4 1
-7 -2
4 5
1 1
Output: The co-ordinates of the two closest points and the smallest distance.
0 0
1 1
1.414214

*/


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

class Point{
public:
    float x, y;
    Point() {x = 0; y = 0;};
    Point(float a, float b){x = a; y = b;};
};

class PointPair{
public:
    Point a;
    Point b;
    float dist;
    PointPair(Point t, Point u){
        a = t; b = u;
        dist = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    };
};

void sort_func(Point * tobeSorted, int lo, int hi, bool id)
{
    //id = 0 for x sort
    //id = 1 for y sort
    //cout<<lo<<' '<<hi<< "dhuksi"<<endl;
    if(lo==hi) return;
    int mid = (lo+hi)/2; //dui bhag -> n(lo to mid)=mid-lo+1 + n(mid+1 to hi) = hi-mid
    sort_func(tobeSorted, lo, mid, id);
    sort_func(tobeSorted, mid+1, hi, id);
    //il - index left...ls - left size
    int ls = mid-lo+1;
    int rs = hi - mid;
    Point * L = new Point[ls];
    Point * R = new Point[rs];
    int il=0, ir=0, is=lo;
    for( ;il<ls; il++,is++){
        L[il] = tobeSorted[is];
        //printf("%f ",L[il].x);
    }
    //cout<<endl;
    for( ; ir<rs; ir++, is++){
        R[ir] = tobeSorted[is];
        //printf("%f ",R[ir].x);
    }
    //cout<<endl;


    il=0, ir=0, is=lo;
    while(ir<rs && il<ls){
        if(id==0){
            if(L[il].x<=R[ir].x){
                tobeSorted[is++] = L[il++];
            }
            else{
                tobeSorted[is++] = R[ir++];
            }
        }
        else {
            if(L[il].y<=R[ir].y){
                tobeSorted[is++] = L[il++];
            }
            else{
                tobeSorted[is++] = R[ir++];
            }
        }
    }
    while(il<ls){
        tobeSorted[is++] = L[il++];
    }
    while(ir<rs){
        tobeSorted[is++] = R[ir++];
    }
    delete[] R;
    delete[] L;
}

PointPair findPair(Point * xsorted, Point * ysorted, int N, int lo, int hi){
    //cout<<"Dhuksi"<<endl;
    int n = hi - lo + 1;
    if(n==2){
        PointPair pp(xsorted[lo], xsorted[hi]);
        return pp;
    }
    else if(n==3){
        PointPair p1(xsorted[lo], xsorted[lo+1]);
        PointPair p2(xsorted[hi], xsorted[lo+1]);
        PointPair p3(xsorted[lo], xsorted[hi]);
        PointPair pp = p1.dist>p2.dist?(p2.dist>p3.dist? p3:p2):(p1.dist>p3.dist?p3:p1);
        return pp;
    }
    int mid = (lo+hi)/2; //dui bhag -> n(lo to mid)=mid-lo+1 + n(mid+1 to hi) = hi-mid

    PointPair pLeft = findPair(xsorted, ysorted, N, lo, mid);
    PointPair pRight = findPair(xsorted, ysorted, N, mid+1, hi);

    PointPair pMin = pLeft.dist>pRight.dist?pRight:pLeft;

    float d = pMin.dist;

    Point * strip = new Point[n];
    int stripsize = 0;
    for(int i = 0; i<N; i++){
        if((ysorted[i].x - xsorted[mid].x) * (ysorted[i].x - xsorted[mid].x) < d){
            strip[stripsize++] = ysorted[i];
        }
    }
    for(int i = 0; i<stripsize; i++){
        for(int j = i+1; j<i+16 && j<stripsize; j++){
            PointPair pingpong(strip[i], strip[j]);
            if(pingpong.dist<d){
                pMin = pingpong;
                d = pingpong.dist;
            }
        }
    }
    delete[] strip;
    return pMin;
}

int main()
{
    int N;
    cin>>N;
    Point * points = new Point[N];
    float a, b;
    for(int i = 0; i<N; i++){
        cin>>a>>b;
        Point p(a,b);
        points[i] = p;
    }

//    cout<<"Main array:\n";
//    for(int i = 0; i<N; i++){
//        printf("(%f,%f) ", points[i].x, points[i].y);
//    }
//    cout<<endl;

    Point * copyforX = new Point[N];
    Point * copyforY = new Point[N];
    //copyforX = points;
    //copyforY = points;
    for(int i = 0; i<N; i++){
        copyforX[i] = points[i];
        copyforY[i] = points[i];
    }
    sort_func(copyforX, 0, N-1, 0);
    sort_func(copyforY, 0, N-1, 1);

//    cout<<"Main array:\n";
//    for(int i = 0; i<N; i++){
//        printf("(%f,%f) ", points[i].x, points[i].y);
//    }
//    cout<<endl;
//
//    cout<<"X sorted:\n";
//    for(int i = 0; i<N; i++){
//        printf("(%f,%f) ", copyforX[i].x, copyforX[i].y);
//    }
//    cout<<endl;
//
//    cout<<"Y sorted:\n";
//    for(int i = 0; i<N; i++){
//        printf("(%f,%f) ", copyforY[i].x, copyforY[i].y);
//    }
//    cout<<endl;

    PointPair ans = findPair(copyforX, copyforY, N, 0, N-1);

    printf("\n\nPoints : (%f, %f) (%f,%f)\nDistance: %f\n", ans.a.x, ans.a.y, ans.b.x, ans.b.y, ans.dist);


//    cout<<endl<<endl<<"Brute Force Solution:"<<endl;
//    PointPair mini(points[0], points[1]);
//    float d = 999999;
//    for(int i = 0; i<N; i++){
//        for(int j = i+1; j<N; j++){
//            PointPair dingdong(points[i], points[j]);
//            if(dingdong.dist<d){
//                d = dingdong.dist;
//                mini = dingdong;
//            }
//        }
//    }
//    printf("Points : (%f, %f) (%f,%f)\nDistance: %f\n", mini.a.x, mini.a.y, mini.b.x, mini.b.y, mini.dist);

    return 0;
}
