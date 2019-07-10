#include"FlowImpl.cpp"

namespace ProconLib{
    template<typename T>
    struct EdgeForMaximumFlow{
        int to;
        T cap;
        int rev;
        EdgeForMaximumFlow(int to,T cap,int rev):to(to),cap(cap),rev(rev){}
    };

    template<typename cap_t=long long,cap_t INF=cap_t(1e9+9)>
    class MaximumFlow:protected FlowImpl<cap_t,INF,EdgeForMaximumFlow<cap_t>>{
        using Edge=EdgeForMaximumFlow<cap_t>;
        using Super=FlowImpl<cap_t,INF,Edge>;
        using Super::N;
        using Super::g;
        using Super::level;
        using Super::iter;
        using Super::bfs;
        using Super::dfs;
        public:
        MaximumFlow(int N):Super(N){}
        void addEdge(int from,int to,cap_t cap);
        cap_t maximumFlow(int s,int t);
    };

    template<typename cap_t,cap_t INF>
    cap_t MaximumFlow<cap_t,INF>::maximumFlow(int s,int t){
        cap_t flow=0;
        while(true){
            bfs(s);
            if(level[t]<0) return flow;
            iter.assign(N,0);
            cap_t f;
            while((f=dfs(s,t,INF))>0){
                flow+=f;
            }
        }
    }
    template<typename cap_t,cap_t INF>
    void MaximumFlow<cap_t,INF>::addEdge(int from,int to,cap_t cap){
        g[from].push_back(Edge(to,cap,int(g[to].size())));
        g[to].push_back(Edge(from,cap_t(0),int(g[from].size())));
    }
}