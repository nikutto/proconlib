#include<bits/stdc++.h>
#include"../LCA.cpp"

using namespace ProconLib;
using namespace std;

struct Edge{
    int to;
};
using Graph=vector<vector<Edge>>;
int main(){
    int n;
    cin>>n;
    Graph g(n);
    for(int i=0;i<n;i++){
        int k;
        cin>>k;
        while(k--){
            int c;
            cin>>c;
            g[i].push_back(Edge{c});
            g[c].push_back(Edge{i});
        }
    }
    LCA<Graph> lca(0,g);
    int q;
    cin>>q;
    while(q--){
        int u,v;
        cin>>u>>v;
        cout<<lca.query(u,v)<<endl;
    }

    return 0;
}