#include<bits/stdc++.h>
#include"../BridgeDetection.cpp"
using namespace std;
using namespace ProconLib;
struct Edge{
    int from,to;
};
using Graph=vector<vector<Edge>>;
int main(){
    int v,e;
    cin>>v>>e;
    Graph g(v);
    for(int i=0;i<e;i++){
        int s,t;
        cin>>s>>t;
        g[s].push_back(Edge{s,t});
        g[t].push_back(Edge{t,s});
    }
    vector<Edge> res=bridgeDetection<Edge,Graph>(g);
    for(auto &e:res){
        if(e.from>e.to) swap(e.from,e.to);
    }
    sort(res.begin(),res.end(),[](Edge lhs,Edge rhs){return make_pair(lhs.from,lhs.to)<make_pair(rhs.from,rhs.to);});
    for(auto &e:res){
        cout<<min(e.from,e.to)<<" "<<max(e.from,e.to)<<endl;
    }
    return 0;
}