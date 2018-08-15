#include<bits/stdc++.h>
using namespace std;

using Weight=long long;
struct Edge{
    int from,to;
    Weight cost;
};
using Edges=vector<Edge>;
using Graph=vector<Edges>;
bool BellmanFord(int s,Graph& g,vector<Weight> &d){
    int n=g.size();
    d[s]=0;
    bool update=true;
    for(int loop=0;update && loop<=n;loop++){
        if(loop==n){
            return false;
        }
        update=false;
        for(int i=0;i<n;i++){
            for(int j=0;j<g[i].size();j++){
                int to=g[i][j].to;
                Weight w=d[i]+g[i][j].cost;
                if(d[to]>w){
                    update=true;
                    d[to]=w;
                }
            }
        }
    }
    return true;
}


//not verified
