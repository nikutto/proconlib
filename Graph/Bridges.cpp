#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int from,to;
};
using Graph=vector<vector<Edge>>;
namespace ProconLib{
    
    //no multiple Edges
    //undirected edges graph
    template<typename edge_t,typename graph_t>
    vector<edge_t> bridgeDetection(graph_t &g){
        int n=g.size();
        vector<int> pre(n,-1),low(n,-1);
        int k=0;
        vector<edge_t> res;
        function<int(int,int)> dfs=[&](int v,int pv){
            pre[v]=k++;
            low[v]=pre[v];
            for(auto &e:g[v]){
                int to=e.to;
                if(to==pv) continue;
                if(pre[to]==-1){
                    low[v]=min(low[v],dfs(to,v));
                    if(low[to]==pre[to]){
                        res.push_back(e);
                    }
                }
                else{
                    low[v]=min(low[v],low[to]);
                }
            }
            return low[v];
        };
        for(int i=0;i<n;i++){
            if(pre[i]==-1){
                dfs(i,-1);
            }
        }
        return res;
    }
}

//verify
using namespace ProconLib;
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
    vector<Edge> res=bridgeDetection<Edge>(g);
    for(auto &e:res){
        if(e.from>e.to) swap(e.from,e.to);
    }
    sort(res.begin(),res.end(),[](Edge lhs,Edge rhs){return make_pair(lhs.from,lhs.to)<make_pair(rhs.from,rhs.to);});
    for(auto &e:res){
        cout<<min(e.from,e.to)<<" "<<max(e.from,e.to)<<endl;
    }
    return 0;
}