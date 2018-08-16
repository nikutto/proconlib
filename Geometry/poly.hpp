#include<vector>
#include "geometry.hpp"
#include "intersect.hpp"

namespace Geometry{
    using Polygon=vector<Point>;
    ld area(const Polygon &ps){
        ld res=0;
        int n=ps.size();
        for(int i=0;i<n;i++){
            res+=cross(ps[i],ps[(i+1)%n]);
        }
        return res/2;
    }
    
    const int OUT=0;
    const int ON=1;
    const int IN=2;
    int is_in_polygon(const Polygon &poly,Point p){
        ld angle=0;
        int n=poly.size();
        for(int i=0;i<n;i++){
            Point a=poly[i],b=poly[(i+1)%n];
            if(isis_sp(Line{a,b},p)) return ON;
            angle+=arg((b-p)/(a-p));
        }
        if(abs(angle)<EPS) return OUT;
        return IN;
    }
}