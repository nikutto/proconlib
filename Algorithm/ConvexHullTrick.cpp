#include<vector>
#include<functional>

namespace ProconLib{

    // ax+b
    // add  : a Monotone
    // get  : x Monotone
    template<typename Line,typename Comp>
    class ConvexHullTrickBase{
        public:
        using value_t=typename Line::value_t;
        std::vector<Line> lines;
        int head=0;
        public:
        void add(Line l);
        Line get(value_t x);
    }; 

    template<typename Line,typename Comp>
    void ConvexHullTrickBase<Line,Comp>::add(Line l){
        if(lines.empty()){
            lines.push_back(l);
            return;
        }
        assert(Comp()(lines.back().a,l.a) || lines.back().a==l.a);
        if(lines.back().a==l.a){
            if(Comp()(lines.back().b,l.b)) lines.pop_back();
            else return;
        }
        while(lines.size()>=2 && Line::isDropMid(*(lines.end()-2),*(lines.end()-1),l)) lines.pop_back();
        lines.push_back(l);        
        head=min(head,(int)(lines.size())-1);
    }

    template<typename Line,typename Comp>
    Line ConvexHullTrickBase<Line,Comp>::get(value_t x){
        while(head+1<lines.size() && Comp()(lines[head].f(x),lines[head+1].f(x))) head++;
        return lines[head];
    }

    template<typename _value_t>
    struct L{
        using value_t=_value_t;
        value_t a,b;
        value_t f(value_t x){return a*x+b;}
        L(value_t a,value_t b):a(a),b(b){}
        static bool isDropMid(L<value_t> l0,L<value_t> l1,L<value_t> l2){
            return -(l1.b-l0.b)*(l2.a-l1.a)>=-(l2.b-l1.b)*(l1.a-l0.a);
        }
    };

    template<typename value_t,typename Comp>
    using ConvexHullTrick=ConvexHullTrickBase<L<value_t>,Comp>;
};