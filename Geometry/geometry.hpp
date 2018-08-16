#include<complex>
namespace Geometry{
    using namespace std;
    using ld=long double;
    using Point=complex<ld>;

    struct Line{
        Point a,b;
    };

    struct Circle{
        Point p;
        ld r;
    };
    const ld EPS=1e-6;
    inline bool EQ(Point a,Point b){return abs(a-b)<EPS;}
    ld dot(Point a,Point b){return real(a)*real(b)+imag(a)*imag(b);}
    ld cross(Point a,Point b){return real(a)*imag(b)-imag(a)*real(b);}

    const int CCW=1;
    const int CW=-1;
    const int BAC=2;
    const int ACB=-2;
    const int ABC=0;
    int ccw(Point a,Point b,Point c){
        b-=a,c-=a;
        if(cross(b,c)>EPS) return CCW; // counter clockwise
        if(cross(b,c)<-EPS) return CW; //clockwise
        if(dot(b,c)<-EPS) return BAC; //b-a-c
        if(abs(b)<abs(c)) return ACB; //a-c-b
        return ABC; //a-b-c (abs(b)>abs(c))
    }
}