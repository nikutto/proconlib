#include<queue>
#include<vector>
#include<utility>
#include<functional>
namespace ProconLib{
    template<typename cost_t>
    constexpr cost_t INF(){return cost_t(1e15);}
    template<class graph_t,typename cost_t,cost_t INF=INF<cost_t>()>
    std::vector<cost_t> Dijkstra(int s,const graph_t& g){
        int n=g.size();
        std::vector<cost_t> res(n,INF);
        std::vector<char> used(n,0);
        res[s]=0;
        std::priority_queue<std::pair<cost_t,int>,std::vector<std::pair<cost_t,int>>,std::greater<>> que;
        que.push(std::make_pair(cost_t(0),s));
        while(!que.empty()){
            auto p=que.top(); que.pop();
            cost_t dist=p.first;
            int v=p.second;
            if(used[v]) continue;
            used[v]=true;
            for(int i=0;i<g[v].size();i++){
                cost_t tdist=dist+g[v][i].weight;
                if(tdist<res[g[v][i].to]){
                    res[g[v][i].to]=tdist;
                    que.push(std::make_pair(tdist,g[v][i].to));
                }
            }
        }
        return res;
    }

    // using Weight=long long;
    // struct Edge{
    //     int to;
    //     Weight weight;
    // };
    // using Edges=vector<Edge>;
    // using Graph=vector<Edges>;
}
