// https://onlinejudge.u-aizu.ac.jp/beta/room.html#ACPC2016Day2/problems/I
#include"../ReRooting.cpp"

#include<bits/stdc++.h>
using namespace std;
using namespace ProconLib;

struct Edge{
    int to;
};

template<typename edge_t>
struct Struct{
    using data_t=pair<int,int>;    
    using value_t=int;
    data_t E(){return make_pair(0,0);};
    data_t merge(data_t x,data_t y){return make_pair(x.first+y.first,max(x.second,y.second));};
    data_t mergeV(data_t x,int v){return x;};
    data_t mergeE(data_t x,const edge_t& e){return make_pair(x.first+2,x.second+1);}
    value_t solve(int v,const std::vector<data_t>& vec){
        int sum=0;
        int ma=0;
        for(int i=0;i<vec.size();i++) sum+=vec[i].first,ma=max(ma,vec[i].second);
        return sum-ma;
    };
}; // no brain solution

using Graph=vector<vector<Edge>>;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    Graph g(n);
    for(int i=0;i+1<n;i++){
        int u,v; cin>>u>>v; u--,v--;
        g[u].push_back(Edge{v});
        g[v].push_back(Edge{u});
    }
    ReRooting<Graph,Struct<Edge>> rr(g);
    auto res=rr.get();
    for(int i=0;i<n;i++) cout<<res[i]<<"\n";
    return 0;
}