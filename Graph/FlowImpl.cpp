#include<vector>
#include<queue>

namespace ProconLib{
    
    template<typename cap_t,cap_t INF,typename edge_t>
    class FlowImpl{
        protected:
        using Edges=std::vector<edge_t>;
        using Graph=std::vector<Edges>;
        int N;
        Graph g;
        std::vector<int> level;
        std::vector<int> iter;
        void bfs(int s);
        cap_t dfs(int v,int t,cap_t f);
        FlowImpl(int N):N(N),g(N){};
    };

    template<typename cap_t,cap_t INF,typename edge_t>
    void FlowImpl<cap_t,INF,edge_t>::bfs(int s){
        level.assign(N,-1);
        std::queue<int> que;
        level[s]=0;
        que.push(s);
        while(!que.empty()){
            int v=que.front(); que.pop();
            for(int i=0;i<g[v].size();i++){
                edge_t &e=g[v][i];
                if(e.cap>0 && level[e.to]<0){
                    level[e.to]=level[v]+1;
                    que.push(e.to);
                }
            }
        }
    }
    template<typename cap_t,cap_t INF,typename edge_t>
    cap_t FlowImpl<cap_t,INF,edge_t>::dfs(int v,int t,cap_t f){
        if(v==t) return f;
        for(int& i=iter[v];i<g[v].size();i++){
            edge_t& e=g[v][i];
            if(e.cap>0 && level[v]<level[e.to]){
                cap_t d=dfs(e.to,t,std::min(f,e.cap));
                if(d>0){
                    e.cap-=d;
                    g[e.to][e.rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }
}