// verify AOJ(GRL/GRL_3_C)(http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C)
#include<bits/stdc++.h>
#include"../SCC.cpp"
struct Edge{
    int to;
};
using namespace std;
using namespace ProconLib;
using Graph=vector<vector<Edge>>;

int main(){
    int V,E;
    cin>>V>>E;
    Graph g(V);
    for(int i=0;i<E;i++) {
        int u,v;
        cin>>u>>v;
        g[u].push_back(Edge{v});
    }
    SCC<Graph> scc(g);
    int q;
    cin>>q;
    auto cmp=scc.getCmp();
    while(q--){
        int u,v;
        cin>>u>>v;
        cout<<(cmp[u]==cmp[v])<<endl;
    }
    return 0;
}
