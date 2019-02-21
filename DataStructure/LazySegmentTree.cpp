#include<bits/stdc++.h>

namespace ProconLib{
    
    template<typename update_t,typename value_t>
    class LazySegmentTree{
        public:
        using UpdateMerger=std::function<update_t(update_t,update_t)>;
        using ValueMerger=std::function<value_t(value_t,value_t)>;
        using Evaluator=std::function<value_t(value_t,update_t)>;

        private:
        int N;
        const value_t E;
        UpdateMerger mergeU;
        ValueMerger mergeV;
        Evaluator eval;
        std::vector<value_t> dat;
        std::vector<update_t> lazy;
        std::vector<int> flag;

        void propagate(int node);
        void applyLazy(int node,update_t x);
        void updateImpl(int l,int r,int k,int lb,int ub,update_t f);
        value_t queryImpl(int l,int r,int k,int lb,int ub);
        value_t getValue(int node){return flag[node] ? eval(dat[node],lazy[node]) : dat[node];}
        
        public:
        LazySegmentTree(int N,Evaluator eval,UpdateMerger mergeU,ValueMerger mergeV,value_t E);
        void update(int l,int r,update_t f);
        value_t query(int a,int b);
    };

    template<typename update_t,typename value_t>
    LazySegmentTree<update_t,value_t>::LazySegmentTree(int N,Evaluator eval,UpdateMerger mergeU,ValueMerger mergeV,value_t E):mergeU(mergeU),mergeV(mergeV),eval(eval),E(E){
        this->N=1;
        while(this->N<N) this->N*=2;
        dat.assign(this->N*2-1,E);
        lazy.assign(this->N*2-1,update_t());
        flag.assign(this->N*2-1,false);
    }
    /*
    template<typename update_t,typename value_t>
    LazySegmentTree<update_t,value_t>::
    */
    template<typename update_t,typename value_t>
    void LazySegmentTree<update_t,value_t>::propagate(int node){
        if(flag[node]){
            flag[node]=false;
            applyLazy(node*2+1,lazy[node]);
            applyLazy(node*2+2,lazy[node]);
            dat[node]=mergeV(getValue(node*2+1),getValue(node*2+2));
        }
    }

    template<typename update_t,typename value_t>
    void LazySegmentTree<update_t,value_t>::applyLazy(int node,update_t x){
        if(flag[node]){
            lazy[node]=mergeU(lazy[node],x);
        }
        else{
            flag[node]=true;
            lazy[node]=x;
        }
    }

    template<typename update_t,typename value_t>
    void LazySegmentTree<update_t,value_t>::updateImpl(int l,int r,int k,int lb,int ub,update_t x){
        if(r<=lb || ub<=l) return;
        if(l<=lb && ub<=r){
            applyLazy(k,x);
            return;
        }
        propagate(k);
        int mid=(lb+ub)/2;
        updateImpl(l,r,k*2+1,lb,mid,x);
        updateImpl(l,r,k*2+2,mid,ub,x);
        dat[k]=mergeV(getValue(k*2+1),getValue(k*2+2));
    }

    template<typename update_t,typename value_t>
    value_t LazySegmentTree<update_t,value_t>::queryImpl(int l,int r,int k,int lb,int ub){
        if(r<=lb || ub<=l) return E;
        if(l<=lb && ub<=r){
            return getValue(k);
        }
        propagate(k);
        int mid=(lb+ub)/2;
        value_t lhs=queryImpl(l,r,k*2+1,lb,mid);
        value_t rhs=queryImpl(l,r,k*2+2,mid,ub);
        return mergeV(lhs,rhs);
    }
    
    template<typename update_t,typename value_t>
    void LazySegmentTree<update_t,value_t>::update(int l,int r,update_t x){
        updateImpl(l,r,0,0,N,x);
    }
    template<typename update_t,typename value_t>
    value_t LazySegmentTree<update_t,value_t>::query(int l,int r){
        return queryImpl(l,r,0,0,N);
    }
    
};

//verify(yukicoder No,318)?
/*
using namespace std;
using namespace ProconLib;
int paste(int x,int y){
    return y;
}
int mymax(int x,int y){
    return max(x,y);
}
int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];

    map<int,vector<int>> mp;
    for(int i=0;i<n;i++) mp[a[i]].push_back(i);
    LazySegmentTree<int,int> seg(n,paste,paste,mymax,0);
    
    for(auto &e:mp){
        int tar=e.first;
        vector<int>& vec=e.second;
        if(vec.empty()) continue;
        seg.update(vec[0],vec.back()+1,tar);
    }
    
    vector<int> b(n);
    for(int i=0;i<n;i++) b[i]=seg.query(i,i+1);
    for(int i=0;i<n;i++){
        cout<<b[i]<<(i+1==n ? "\n" : " ");
    }
    return 0;
}
*/