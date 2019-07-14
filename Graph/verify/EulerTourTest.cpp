// AOJ(DRL_5_D) Range Query on a Tree
#include<bits/stdc++.h>
#include"../EulerTour.cpp"
#include"../../DataStructure/SegmentTree.cpp"
using namespace std;
using namespace ProconLib;

struct Edge{
    int to;
};

struct Monoid{
    using value_t=int;
    static constexpr value_t E(){return 0;}
    static value_t op(value_t lhs,value_t rhs){return lhs+rhs;}
};    

using Graph=vector<vector<Edge>>;
int PathQueryVerify(){
    int n;
    cin>>n;
    Graph g(n);
    vector<int> par(n,-1);
    vector<int> val(n,0);
    for(int i=0;i<n;i++){
        int k; cin>>k;
        while(k--){
            int c; cin>>c;
            par[c]=i;
            g[i].push_back(Edge{c});
            g[c].push_back(Edge{i});
        }
    }
    EulerTour<Graph> et(0,g);
    SegmentTree<Monoid> seg(2*n);

    int q; cin>>q;
    while(q--){
        int type; cin>>type;
        if(!type){
            int v,w; cin>>v>>w;
            val[v]+=w;
            seg.update(et.in(v),val[v]);
            seg.update(et.out(v),-val[v]);
        }
        else{
            int u; cin>>u;
            cout<<seg.query(et.in(0),et.in(u)+1)<<endl;
        }
    }
}

int main(){
    PathQueryVerify();
}