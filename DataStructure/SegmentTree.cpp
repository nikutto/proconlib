#include<vector>

namespace ProconLib{
    struct MonoidExample{
        using value_t=int;
        static constexpr value_t E(){return 0;}
        static value_t op(value_t lhs,value_t rhs){return lhs+rhs;}
    };
    template<class Monoid>
    class SegmentTree{
        public: 
        using value_t= typename Monoid::value_t;
        private:
        std::vector<value_t> dat;
        int N;
        static int calcN(int n){int res=1; while(res<n) res*=2; return res;}
        value_t queryImpl(int a,int b,int k,int l,int r);

        public:
        SegmentTree(int N);
        void update(int pos,value_t val);        
        void updateALL(std::vector<value_t> x);
        value_t query(int a,int b);
    };

    template<typename Monoid>
    SegmentTree<Monoid>::SegmentTree(int n):N(calcN(n)),dat(2*N-1,Monoid::E()){}

    template<typename Monoid>
    void SegmentTree<Monoid>::update(int pos,value_t val){
        pos+=N-1;
        dat[pos]=val;
        while(pos!=0){
            int par=(pos-1)/2;
            dat[par]=Monoid::op(dat[par*2+1],dat[par*2+2]);
            pos=par;
        }
    }

    template<typename Monoid>
    void SegmentTree<Monoid>::updateALL(std::vector<value_t> x){
        for(int i=0;i<x.size();i++) dat[N-1+i]=x[i];
        for(int i=N-2;i>=0;i--) dat[i]=Monoid::op(dat[i*2+1],dat[i*2+2]);
    }

    template<typename Monoid>
    typename SegmentTree<Monoid>::value_t SegmentTree<Monoid>::query(int a,int b){
        return queryImpl(a,b,0,0,N);
    }

    template<typename Monoid>
    typename SegmentTree<Monoid>::value_t SegmentTree<Monoid>::queryImpl(int a,int b,int k,int l,int r){
        if(a<=l && r<=b) return dat[k];
        if(r<=a || b<=l) return Monoid::E();
        int mid=(l+r)/2;
        value_t c1v=queryImpl(a,b,k*2+1,l,mid);
        value_t c2v=queryImpl(a,b,k*2+2,mid,r);
        return Monoid::op(c1v,c2v);
    }
}

