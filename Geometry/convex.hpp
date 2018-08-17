#include "geometry.hpp"
#include<vector>
#include<algorithm>

namespace Geometry{
    vector<Point> convexFull(const vector<Point>& ps){
        int n=ps.size();
        if(n<=1) return ps;
        auto cmp=[](const Point &lhs,const Point &rhs){
            return real(lhs)==real(rhs) ? imag(lhs)<imag(rhs) : real(lhs)<real(rhs);
        };
        sort(ps.begin(),ps.end(),cmp);
        int k=0;
        vector<Point> qs(n*2);
        for(int i=0;i<n;i++){
            while(k>=2 && ccw(qs[k-2],qs[k-1],ps[i])<=0) --k;
            qs[k++]=ps[i];
        }
        int t=k;
        for(int i=n-2;i>=0;i--){
            while(k>t && ccw(qs[k-2],qs[k-1],ps[i])<=0) --k;
            qs[k++]=ps[i];
        }
        qs.resize(k-1);
        return qs;
    }
}