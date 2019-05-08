#include<bits/stdc++.h>
#include"../TopologicalSort.cpp"
using namespace std;
using namespace ProconLib;

struct Edge{
    int to;
};

using Edges=vector<Edge>;
using Graph=vector<Edges>;
int main(){
    int n,m;
    cin>>n>>m;
    Graph g(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back({v});
    }

    auto res=TopologicalSort(g);
    for(auto v:res)cout<<v<<endl;
    return 0;
}