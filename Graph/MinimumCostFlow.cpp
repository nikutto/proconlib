#include<vector>
#include<queue>
#include<utility>
#include<algorithm>
#include"FlowImpl.cpp"

namespace ProconLib{

    template<typename cap_t,typename cost_t>
    struct EdgeForMinimumCostFlow{
        int to;
        cap_t cap;
        int rev;
        cost_t cost;
        EdgeForMinimumCostFlow(int to,cap_t cap,int rev,cost_t cost):to(to),cap(cap),rev(rev),cost(cost){}
    };

    template<typename cap_t=long long,typename cost_t=long long,bool hasNegativeCost=false,cap_t INF_cap=cap_t(1e9+9),cost_t INF_cost=cost_t(1e9+9)>
    class MinimumCostFlow:protected FlowImpl<cap_t,INF_cap,EdgeForMinimumCostFlow<cap_t,cost_t>>{
        using Edge=EdgeForMinimumCostFlow<cap_t,cost_t>;
        using Super=FlowImpl<cap_t,INF_cap,Edge>;
        using Super::N;
        using Super::g;
        using Super::level;
        using Super::iter;
        using Super::bfs;
        using Super::dfs;
        public:
        MinimumCostFlow(int N):Super(N){}
        void addEdge(int from,int to,cap_t cap,cost_t cost);
        cost_t minimumCostFlow(int s,int t,cap_t f);
    };

    template<typename cap_t,typename cost_t,bool hasNegativeCost,cap_t INF_cap,cost_t INF_cost>
    void MinimumCostFlow<cap_t,cost_t,hasNegativeCost,INF_cap,INF_cost>::addEdge(int from,int to,cap_t cap,cost_t cost){
        g[from].push_back({to,cap,int(g[to].size()),cost});
        g[to].push_back({from,cost_t(0),int(g[from].size())-1,-cost});
    }

    template<typename cap_t,typename cost_t,bool hasNegativeCost,cap_t INF_cap,cost_t INF_cost>
    cost_t MinimumCostFlow<cap_t,cost_t,hasNegativeCost,INF_cap,INF_cost>::minimumCostFlow(int s,int t,cap_t f){
        using P=std::pair<cost_t,int>;
        cost_t res=0;
        std::vector<cost_t> h(N,0);
        std::vector<int> used(N),preve(N),prevv(N);
        std::vector<cost_t> dist(N);
        while(f>0){    
            std::fill(dist.begin(),dist.end(),INF_cost);
            dist[s]=0;
            if(!hasNegativeCost){
                //Dijkstra
                std::fill(used.begin(),used.end(),0);
                std::priority_queue<P,std::vector<P>,std::greater<P>> que;
                que.push(make_pair(cost_t(0),s));
                while(!que.empty()){
                    P p=que.top(); que.pop();
                    int v=p.second;
                    if(used[v]) continue;
                    used[v]=true;
                    for(int i=0;i<g[v].size();i++){
                        Edge &e=g[v][i];
                        if(e.cap>0 && dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
                            dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
                            prevv[e.to]=v;
                            preve[e.to]=i;
                            que.push(make_pair(dist[e.to],e.to));
                        }
                    }
                }
            }else{
                //Bermanford
                bool update=true;
                while(update){
                    update=false;
                    for(int v=0;v<N;v++){
                        if(dist[v]==INF_cost) continue;
                        for(int i=0;i<g[v].size();i++){
                            Edge &e=g[v][i];
                            if(e.cap>0 && dist[e.to]>dist[v]+e.cost){
                                dist[e.to]=dist[v]+e.cost;
                                prevv[e.to]=v;
                                preve[e.to]=i;
                                update=true;
                            }
                        }
                    }
                }
            }

            if(dist[t]==INF_cost){
                return -1;
            }
            if(!hasNegativeCost){
                for(int v=0;v<N;v++) h[v]+=dist[v];
            }
            cost_t d=f;
            for(int v=t;v!=s;v=prevv[v]){
                d=min(d,g[prevv[v]][preve[v]].cap);
            }
            f-=d;
            if(!hasNegativeCost){
                res+=d*h[t];
            }else{
                res+=d*dist[t];
            }
            for(int v=t;v!=s;v=prevv[v]){
                Edge& e=g[prevv[v]][preve[v]];
                e.cap-=d;
                g[v][e.rev].cap+=d;
            }
        }
        return res;
    }
}