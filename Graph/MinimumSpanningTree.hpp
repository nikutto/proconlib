#include<bits/stdc++.h>
#include"UnionFind.hpp"
using namespace std;

using Weight=long long;
struct Edge{
    int from,to;
    Weight weight;
};
bool operator<(const Edge& lhs,const Edge& rhs){
    return lhs.weight<rhs.weight;
}

using Edges=vector<Edge>;
using Graph=vector<Edges>;

Edges MinimumSpanningTree(int n,Edges edges){
    sort(edges.begin(),edges.end());
    Edges res;
    UnionFind u(n);
    for(int i=0;i<edges.size();i++){
        if(!u.same(edges[i].from,edges[i].to)){
            res.push_back(edges[i]);
            u.unite(edges[i].from,edges[i].to);
        }
    }
    return res;
}

Edges MinimumSpanningTree(const Graph& g){
    Edges edges;
    for(int i=0;i<g.size();i++){
        copy(g[i].begin(),g[i].end(),back_inserter(edges));
    }
    auto res=MinimumSpanningTree(g.size(),edges);
    return res;
}

/*verify(AOJ ALDS1_12_A)
int main(){
    int n;
    cin>>n;
    Graph g(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            Weight c;
            cin>>c;
            if(c==-1) continue;
            g[i].push_back({i,j,c});
        }
    }
    auto mst=MinimumSpanningTree(g);
    cout<<accumulate(mst.begin(),mst.end(),Weight(0),[](const Weight& lhs,const Edge& rhs){return lhs+rhs.weight;})<<endl;
    return 0;
}
*/