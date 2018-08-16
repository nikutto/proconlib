#include "geometry.hpp"
#include<vector>
#include<cassert>

namespace Geometry{
    bool isis_ll(Line x,Line y){
        return !EQ(cross(x.a-x.b,y.a-y.b),ld(0));
    }

    bool isis_ss(Line x,Line y){
        return ccw(x.a,x.b,y.a)*ccw(x.a,x.b,y.b)<=0 && ccw(y.a,y.b,x.a)*ccw(y.a,y.b,x.b)<=0;
    }

    bool isis_ls(Line l,Line s){
        return cross(l.b-l.a,s.a-l.a)*cross(l.b-l.a,s.b-l.a)<EPS;
    }

    Point is_ll(Line x,Line y){
        return x.a+(x.b-x.a)*abs(cross(x.a-y.a,y.b-y.a))/abs(cross(x.b-x.a,y.b-y.a));
    }

    Point proj(Line l,Point p){
        ld t=dot(l.b-l.a,p-l.a)/norm(l.b-l.a);
        return l.a+(l.b-l.a)*t;
    }
    ld dist_lp(Line l,Point p){
        Point x=l.b-l.a;
        Point y=p-l.a;
        return abs(cross(x,y))/abs(x);
    }

    ld dist_sp(Line l,Point p){
        if(dot(p-l.a,l.b-l.a)<EPS) return abs(p-l.a);
        if(dot(p-l.b,l.a-l.b)<EPS) return abs(p-l.b);
        return dist_lp(l,p);
    }

    ld dist_ss(Line x,Line y){
        if(isis_ss(x,y)) return 0;
        ld a=min(dist_sp(x,y.a),dist_sp(x,y.b));
        ld b=min(dist_sp(y,x.a),dist_sp(y,x.b));
        return min(a,b);
    }

    vector<Point> is_cc(Circle c0,Circle c1){
        vector<Point> res;
        ld d=abs(c0.p-c1.p);
        ld lm=(d*d+c0.r*c0.r-c1.r*c1.r)/(2*d);
        ld dl=c0.r*c0.r-lm*lm;
        if(abs(dl)<EPS){
            res.push_back(c0.p+(c1.p-c0.p)*lm/d);
            return res;
        }
        if(dl<ld(0)) return res;
        ld l=sqrt(dl);
        Point dir=(c1.p-c0.p)/d;
        res.push_back(c0.p+dir*Point(lm,l));
        res.push_back(c0.p+dir*Point(lm,-l));
        return res;
    }

    vector<Point> is_lc(Line l,Circle c){
        vector<Point> res;
        ld d=dist_lp(l,c.p);
        if(d>c.r+EPS){
            return res;
        }
        Point mp=proj(l,c.p);
        if(abs(d-c.r)<EPS){
            res.push_back(mp);
            return res;
        }
        ld len=sqrt(c.r*c.r-d*d);
        Point dir=(l.a-l.b)/abs(l.a-l.b);
        res.push_back(mp+dir*len);
        res.push_back(mp-dir*len);
        return res;
    }

    vector<Point> is_sc(Line s,Circle c){
        vector<Point> res;
        auto v=is_lc(s,c);
        for(auto &e:v){
            if(ccw(s.a,e,s.b)==ACB){
                res.push_back(e);
            }
        }
        return res;
    }

    vector<Line> tangent_cp(Circle c,Point p){
        vector<Line> res;
        Point v=c.p-p;
        ld d=abs(v);
        if(abs(d-c.r)<EPS){
            Point dir=v*Point(0,1);
            res.push_back(Line{p,p+v});
            return res;
        }
        if(d<c.r){
            return res;
        }
        ld l=sqrt(d*d-c.r*c.r);
        Point v0=v*Point(l/d,c.r/d);
        Point v1=v*Point(l/d,-c.r/d);
        res.push_back(Line{p,p+v0});
        res.push_back(Line{p,p+v1});
        return res;
    }

    vector<Line> tangent_cc(Circle c0,Circle c1){
        vector<Line> res;
        if(abs(c1.p-c0.p)>c0.r+c1.r-EPS){
            Point mp=(c0.p*c1.r+c1.p*c0.r)/(c0.r+c1.r);
            res=tangent_cp(c0,mp);
        }
        if(abs(c1.r-c0.r)>EPS){
            Point om=(-c0.p*c1.r+c1.p*c0.r)/(c0.r-c1.r);
            res=tangent_cp(c0,om);
        }
        else{
            Point v=c1.p-c0.p;
            ld d=abs(v);
            Point p0=v*Point(0,c0.r/d);
            Point p1=v*Point(0,-c0.r/d);
            res.push_back(Line{p0,p0+v});
            res.push_back(Line{p1,p1+v});
        }        
        return res;
    }
}