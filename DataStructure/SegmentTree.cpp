#include<bits/stdc++.h>

namespace ProconLib{
    template<typename T>
    class SegmentTree{
        std::vector<T> dat;
        int N;
        T E;
        std::function<T(T,T)> merge;
        T query_impl(int a,int b,int k,int l,int r);
        public:
        SegmentTree(int N,std::function<T(T,T)> merge,T E);
        void update(int pos,T val);        
        void updateALL(std::vector<T> x);
        T query(int a,int b);
    };

    template<typename T>
    SegmentTree<T>::SegmentTree(int N,std::function<T(T,T)> merge,T E):E(E),merge(merge){
        assert(N>=0);
        this->N=1;
        while(this->N<N){
            (this->N)*=2;
        }
        dat.assign(this->N*2-1,E);
    }

    template<typename T>
    void SegmentTree<T>::update(int pos,T val){
        pos+=N-1;
        dat[pos]=val;
        while(pos!=0){
            int par=(pos-1)/2;
            dat[par]=merge(dat[par*2+1],dat[par*2+2]);
            pos=par;
        }
    }

    template<typename T>
    void SegmentTree<T>::updateALL(std::vector<T> x){
        assert(x.size()<=N);
        for(int i=0;i<x.size();i++) dat[N-1+i]=x[i];
        for(int i=N-2;i>=0;i--) dat[i]=merge(dat[i*2+1],dat[i*2+2]);
    }

    template<typename T>
    T SegmentTree<T>::query(int a,int b){
        assert(a<=b);
        return query_impl(a,b,0,0,N);
    }

    template<typename T>
    T SegmentTree<T>::query_impl(int a,int b,int k,int l,int r){
        if(a<=l && r<=b) return dat[k];
        if(r<=a || b<=l) return E;
        int mid=(l+r)/2;
        T c1v=query_impl(a,b,k*2+1,l,mid);
        T c2v=query_impl(a,b,k*2+2,mid,r);
        return merge(c1v,c2v);
    }
}

/*verfy(AOJ DSL_2/A)*/
using namespace ProconLib;
int mymin(int a,int b){return std::min(a,b);}
int main(){
    int n,q;
    std::cin>>n>>q;
    SegmentTree<int> seg(n,mymin,int((1u<<31)-1));
    for(int i=0;i<q;i++){
        int com,x,y;
        std::cin>>com>>x>>y;
        if(com){
            y++;
            std::cout<<seg.query(x,y)<<std::endl;
        }
        else{
            seg.update(x,y);
        }
    }
    return 0;
}
