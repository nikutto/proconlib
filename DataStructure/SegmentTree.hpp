#include<bits/stdc++.h>
using namespace std;

using T=long long int;
class SegmentTree{
    vector<T> dat;
    int N;
    T E;
    function<T(T,T)> merge;
    T query_impl(int a,int b,int k,int l,int r);
    public:
    SegmentTree(size_t N,function<T(T,T)> merge,T E);
    void update(int pos,T val);        
    T query(int a,int b);
};

SegmentTree::SegmentTree(size_t N,function<T(T,T)> merge,T E):E(E),merge(merge){
    this->N=1;
    while(this->N<N){
        (this->N)*=2;
    }
    dat.assign(this->N*2-1,E);
}

void SegmentTree::update(int pos,T val){
    pos+=N-1;
    dat[pos]=val;
    while(pos!=0){
        int par=(pos-1)/2;
        int c1=par*2+1;
        int c2=par*2+2;
        dat[par]=merge(dat[c1],dat[c2]);
        pos=par;
    }
}

T SegmentTree::query(int a,int b){
    assert(a<=b);
    return query_impl(a,b,0,0,N);
}

T SegmentTree::query_impl(int a,int b,int k,int l,int r){
    if(a<=l && r<=b) return dat[k];
    if(r<=a || b<=l) return E;
    int mid=(l+r)/2;
    T c1v=query_impl(a,b,k*2+1,l,mid);
    T c2v=query_impl(a,b,k*2+2,mid,r);
    return merge(c1v,c2v);
}


/*verfy(AOJ DSL_2/A)
T mymin(T a,T b){return min(a,b);}
int main(){
    int n,q;
    cin>>n>>q;
    SegmentTree seg(n,mymin,int((1u<<31)-1));
    for(int i=0;i<q;i++){
        int com,x,y;
        cin>>com>>x>>y;
        if(com){
            y++;
            cout<<seg.query(x,y)<<endl;
        }
        else{
            seg.update(x,y);
        }
    }
    return 0;
}
*/