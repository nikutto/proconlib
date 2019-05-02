// AOJ(GRL_1_A)
#include<iostream>
#include<vector>
#include"../Dijkstra.cpp"

using namespace std;
using namespace ProconLib;
using Weight=long long;
struct Edge{
    int to;
    Weight weight;
};
using Edges=vector<Edge>;
using Graph=vector<Edges>;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,r;
    cin>>n>>m>>r;
    Graph g(n);
    for(int i=0;i<m;i++){
        int u,v;
        Weight d;
        cin>>u>>v>>d;
        g[u].push_back(Edge{v,d});
    }
    
    auto d=Dijkstra<Graph,Weight>(r,g);
    for(int i=0;i<n;i++){
        if(d[i]==INF<Weight>()) cout<<"INF\n";
        else cout<<d[i]<<"\n";
    }

    return 0;
}
