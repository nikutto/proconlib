#include<vector>
#include<iostream>
#include"../BellmanFord.cpp"

using namespace std;
using Weight=long long;
struct Edge{
    int to;
    Weight cost;
};
using Edges=std::vector<Edge>;
using Graph=std::vector<Edges>;
using namespace ProconLib;
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
    vector<Weight> d(n);
    if(BellmanFord<Graph,Weight>(r,g,d)){
        for(int i=0;i<n;i++){
            if(d[i]!=INF<Weight>()) cout<<d[i]<<"\n";
            else cout<<"INF\n";
        }
    }
    else{
        cout<<"NEGATIVE CYCLE\n";
    }
    

    return 0;
}