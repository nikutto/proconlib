#include"LazySegmentTree.cpp"

namespace ProconLib{

    //verified when l=0
    template<typename MUStruct>
    class BSLazySegmentTree:public LazySegmentTree<MUStruct>{
        public:
        using LazySegmentTree<MUStruct>::N;
        using typename LazySegmentTree<MUStruct>::value_t;
        using typename LazySegmentTree<MUStruct>::Monoid;
        using LazySegmentTree<MUStruct>::getValue;
        using LazySegmentTree<MUStruct>::propagate;
        protected:
        template<typename Judge>
        int searchImpl(int l,int k,int lb,int ub,value_t& v){
            if(ub<=l) return N+1;
            if(k>=N-1){
                v=Monoid::op(v,getValue(k));
                return Judge::op(v) ? ub : N+1;
            }
            propagate(k);
            int mid=(lb+ub)/2;
            if(lb<l){
                int ret=searchImpl<Judge>(l,k*2+1,lb,mid,v);
                if(ret<=N) return ret;
                if(Judge::op(Monoid::op(v,getValue(k*2+2)))){
                    return searchImpl<Judge>(l,k*2+2,mid,ub,v);
                }
                else{
                    v=Monoid::op(v,getValue(k*2+2));
                    return N+1;
                }
            }
            else{
                if(Judge::op(Monoid::op(v,getValue(k*2+1)))){
                    return searchImpl<Judge>(l,k*2+1,lb,mid,v);
                }
                else{
                    v=Monoid::op(v,getValue(k*2+1));
                    return searchImpl<Judge>(l,k*2+2,mid,ub,v);
                }
            }
        }

        public:
        BSLazySegmentTree(int N):LazySegmentTree<MUStruct>(N){}
        
        // return r
        // s.t.
        // judge(query(l,i))==false if i<r
        // judge(query(l,i))==true  if r<=i<=N
        template<typename Judge>
        int search(int l){
            if(Judge::op(Monoid::E())) return l;
            value_t v=Monoid::E();
            return searchImpl<Judge>(l,0,0,N,v);
        }
    };
}