#include<queue>
#include<utility>
#include<vector>
namespace ProconLib{
    template<class graph_t,typename weight_t>
    weight_t Prim(const graph_t& g){
        using Item=std::pair<weight_t,int>;
        std::priority_queue<Item,std::vector<Item>,std::greater<>> que;
        std::vector<int> used(g.size());
        auto Push=[&](int v){
            used[v]=true;
            for(auto &e:g[v]){
                if(!used[e.to]) que.push(std::make_pair(e.weight,e.to));
            }
        };
        Push(0);
        weight_t res=0;
        while(!que.empty()){
            auto tmp=que.top(); que.pop();
            int v=tmp.second;
            if(used[v]) continue;
            res+=tmp.first;
            Push(v);
        }
        return res;
    }
}