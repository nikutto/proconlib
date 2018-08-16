#include "geometry.hpp"

bool isis_ll(Line x,Line y){
    return EQ(cross(x.a-x.b,y.a-y.b),ld(0));
}

ld dist_lp(Line l,P p){
    P x=l.b-l.a;
    P y=p-l.a;
    return abs(cross(x,y))/abs(x);
}

ld dist_sp(Line l,P p){
    if(dot(p-l.a,l.b-l.a)<EPS) return abs(p-l.a);
    if(dot(p-l.b,l.a-l.b)<EPS) return abs(p-l.b);
    return dist_lp(l,p);
}

bool isis_ss(Line x,Line y){
    return ccw(x.a,x.b,y.a)*ccw(x.a,x.b,y.b)<=0 && ccw(y.a,y.b,x.a)*ccw(y.a,y.b,x.b)<=0;
}