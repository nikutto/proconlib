#include<bits/stdc++.h>
#include"../Prim.cpp"
using namespace std;
using namespace ProconLib;

struct Edge{
    int to;
    int weight;
};
using Graph=vector<vector<Edge>>;
const int SIZE=50;
int main(){
    int v,e;
    cin>>v>>e;
    Graph g(v);
    for(int i=0;i<e;i++){
        int s,t,w;
        cin>>s>>t>>w;
        g[s].push_back(Edge{t,w});
        g[t].push_back(Edge{s,w});
    }
    int res=0;
    for(int i=0;i<SIZE;i++){
        res=Prim<Graph,int>(g);
    }
    cout<<res<<endl;
    return 0;
}