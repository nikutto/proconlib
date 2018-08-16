#include<complex>

using namespace std;
using ld=long double;
using P=complex<ld>;

struct Line{
    P a,b;
};
const ld EPS=1e-6;
inline bool EQ(P a,P b){return abs(a-b)<EPS;}
ld dot(P a,P b){return real(a)*real(b)+imag(a)*imag(b);}
ld cross(P a,P b){return real(a)*imag(b)-imag(a)*real(b);}

int ccw(P a,P b,P c){
    b-=a,c-=a;
    if(cross(b,c)>EPS) return 1; // counter clockwise
    if(cross(b,c)<-EPS) return -1; //clockwise
    if(dot(b,c)<-EPS) return 2; //c-a-b
    if(abs(b)<abs(c)) return -2; //a-c-b
    return 0; //a-b-c (abs(b)>abs(c))
}