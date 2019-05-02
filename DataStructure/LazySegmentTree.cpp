#include<vector>

namespace ProconLib{
    
    template<class MUStruct>
    class LazySegmentTree{
        public:
        using Monoid=typename MUStruct::Monoid;
        using Update=typename MUStruct::Update;
        using value_t=typename Monoid::value_t;
        using update_t=typename Update::update_t;

        private:

        int N;
        std::vector<value_t> dat;
        std::vector<update_t> lazy;
        std::vector<char> flag;

        static int calcN(int n){int res=1; while(res<n) res*=2; return res;};
        void propagate(int node,int l,int r);
        void applyLazy(int node,update_t x);
        void applyImpl(int l,int r,int k,int lb,int ub,update_t f);
        void updateImpl(int pos,int k,int lb,int ub,value_t x);
        value_t queryImpl(int l,int r,int k,int lb,int ub);
        value_t getValue(int node,int l,int r){return flag[node] ? MUStruct::evaluate(dat[node],lazy[node],l,r) : dat[node];}
        
        public:
        LazySegmentTree(int N);
        void apply(int l,int r,update_t f);
        void update(int pos,value_t v);
        value_t query(int a,int b);
    };

    // struct MUStructExample{
    //     struct Monoid{
    //         using value_t=int;
    //         static constexpr value_t E(){return 0;}
    //         static value_t op(value_t lhs,value_t rhs){ return lhs+rhs;}
    //     };
    //     struct Update{
    //         using update_t = int;
    //         static update_t op(update_t lhs,update_t rhs){ return lhs+rhs;}
    //     };
    //     static Monoid::value_t evaluate(Monoid::value_t v,Update::update_t u,int l,int r){ return v+u*(r-l);}
    // };

    template<class MUStruct>
    LazySegmentTree<MUStruct>::LazySegmentTree(int n):N(calcN(n)),dat(N*2-1,Monoid::E()),lazy(N*2-1),flag(N*2-1,false){}
    
    template<class MUStruct>
    void LazySegmentTree<MUStruct>::propagate(int node,int l,int r){
        if(flag[node]){
            flag[node]=false;
            applyLazy(node*2+1,lazy[node]);
            applyLazy(node*2+2,lazy[node]);
            int mid=(l+r)/2;
            dat[node]=Monoid::op(getValue(node*2+1,l,mid),getValue(node*2+2,mid,r));
        }
    }

    template<class MUStruct>
    void LazySegmentTree<MUStruct>::applyLazy(int node,update_t x){
        if(flag[node]){
            lazy[node]=Update::op(lazy[node],x);
        }
        else{
            flag[node]=true;
            lazy[node]=x;
        }
    }

    template<class MUStruct>
    void LazySegmentTree<MUStruct>::applyImpl(int l,int r,int k,int lb,int ub,update_t x){
        if(r<=lb || ub<=l) return;
        if(l<=lb && ub<=r){
            applyLazy(k,x);
            return;
        }
        propagate(k,lb,ub);
        int mid=(lb+ub)/2;
        updateImpl(l,r,k*2+1,lb,mid,x);
        updateImpl(l,r,k*2+2,mid,ub,x);
        dat[k]=Monoid::op(getValue(k*2+1,lb,ub),getValue(k*2+2,lb,ub));
    }

    template<class MUStruct>
    void LazySegmentTree<MUStruct>::updateImpl(int pos,int k,int lb,int ub,value_t x){
        if(!(lb<=pos && pos<ub))return;
        if(pos==lb && pos==ub-1){
            flag[k]=false;
            dat[k]=x;
            return;
        }
        propagate(k,lb,ub);
        int mid=(lb+ub)/2;
        updateImpl(pos,k*2+1,lb,mid,x);
        updateImpl(pos,k*2+2,mid,ub,x);
        dat[k]=Monoid::op(getValue(k*2+1,lb,ub),getValue(k*2+2,lb,ub));
    }

    template<class MUStruct>
    typename LazySegmentTree<MUStruct>::value_t LazySegmentTree<MUStruct>::queryImpl(int l,int r,int k,int lb,int ub){
        if(r<=lb || ub<=l) return Monoid::E();
        if(l<=lb && ub<=r){
            return getValue(k,lb,ub);
        }
        propagate(k,lb,ub);
        int mid=(lb+ub)/2;
        value_t lhs=queryImpl(l,r,k*2+1,lb,mid);
        value_t rhs=queryImpl(l,r,k*2+2,mid,ub);
        return Monoid::op(lhs,rhs);
    }
    
    template<class MUStruct>
    void LazySegmentTree<MUStruct>::apply(int l,int r,update_t x){
        applyImpl(l,r,0,0,N,x);
    }

    template<class MUStruct>
    void LazySegmentTree<MUStruct>::update(int pos,value_t x){
        updateImpl(pos,0,0,N,x);
    }

    template<class MUStruct>
    typename LazySegmentTree<MUStruct>::value_t LazySegmentTree<MUStruct>::query(int l,int r){
        return queryImpl(l,r,0,0,N);
    }
};
