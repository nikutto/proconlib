#include<vector>
#include<algorithm>
namespace ProconLib{
    
    //no multiple Edges
    //undirected edges graph
    template<class edge_t,class graph_t=std::vector<std::vector<edge_t>>>
    std::vector<edge_t> bridgeDetection(const graph_t& g){
        int n=g.size();
        std::vector<int> pre(n,-1);
        std::vector<int> low(n,-1);
        std::vector<edge_t> res;
        int id=0;
        auto dfs=[&](int v,int prev,auto& f) -> int{
            pre[v]=id++;
            low[v]=pre[v];
            for(auto &e:g[v]){
                if(e.to==prev) continue;
                if(pre[e.to]==-1){
                    low[v]=std::min(low[v],f(e.to,v,f));
                    if(pre[e.to]==low[e.to]){
                        res.push_back(e);
                    }
                }
                else{
                    low[v]=std::min(low[v],pre[e.to]);
                }
            }
            return low[v];
        };
        dfs(0,-1,dfs);
        return res;
    }
}

#include<bits/stdc++.h>
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