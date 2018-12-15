#include<bits/stdc++.h>
using namespace std;
using Weight=long long;

struct Edge{
    int to;
    Weight cap,rev;
    Weight cost;
};

using Edges=vector<Edge>;
using Graph=vector<Edges>;

class Flow{
    const Weight INF=1e9+7;
    const bool isNegative=false;
    int N;
    Graph g;
    vector<int> level;
    vector<int> iter;
    void bfs(int s);
    Weight dfs(int v,int t,Weight f);
    public:
    Flow(int N):N(N),g(N){};
    void addEdge(int from,int to,Weight cap);
    void addEdge(int from,int to,Weight cap,Weight cost);
    Weight maxFlow(int s,int t);
    Weight minCostFlow(int s,int t,Weight f);
};


void Flow::addEdge(int from,int to,Weight cap){
    g[from].push_back({to,cap,int(g[to].size()),0});
    g[to].push_back({from,Weight(0),int(g[from].size())-1,0});
}

void Flow::addEdge(int from,int to,Weight cap,Weight cost){
    g[from].push_back({to,cap,int(g[to].size()),cost});
    g[to].push_back({from,Weight(0),int(g[from].size())-1,-cost});
}
Weight Flow::maxFlow(int s,int t){
    Weight flow=0;
    while(true){
        bfs(s);
        if(level[t]<0) return flow;
        iter.assign(N,0);
        Weight f;
        while((f=dfs(s,t,INF))>0){
            flow+=f;
        }
    }
}
void Flow::bfs(int s){
    level.assign(N,-1);
    queue<int> que;
    level[s]=0;
    que.push(s);
    while(!que.empty()){
        int v=que.front(); que.pop();
        for(int i=0;i<g[v].size();i++){
            Edge &e=g[v][i];
            if(e.cap>0 && level[e.to]<0){
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}

Weight Flow::dfs(int v,int t,Weight f){
    if(v==t) return f;
    for(int& i=iter[v];i<g[v].size();i++){
        Edge& e=g[v][i];
        if(e.cap>0 && level[v]<level[e.to]){
            Weight d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                g[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}

Weight Flow::minCostFlow(int s,int t,Weight f){
    using P=pair<Weight,int>;
    Weight res=0;
    vector<Weight> h(N,0);
    vector<int> used(N),preve(N),prevv(N);
    vector<Weight> dist(N);
    while(f>0){    
        fill(dist.begin(),dist.end(),INF);
        dist[s]=0;
        if(!isNegative){
            //Dijkstra
            fill(used.begin(),used.end(),0);
            priority_queue<P,vector<P>,greater<P>> que;
            que.push(make_pair(Weight(0),s));
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
                    if(dist[v]==INF) continue;
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

        if(dist[t]==INF){
            return -1;
        }
        if(!isNegative){
            for(int v=0;v<N;v++) h[v]+=dist[v];
        }
        Weight d=f;
        for(int v=t;v!=s;v=prevv[v]){
            d=min(d,g[prevv[v]][preve[v]].cap);
        }
        f-=d;
        if(!isNegative){
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
//verify for maxFlow AOJ(GRL_6_A)
/*
int main(){
    int v,e;
    cin>>v>>e;
    Flow g(v);
    for(int i=0;i<e;i++){
        int u,v,c;
        cin>>u>>v>>c;
        g.addEdge(u,v,c);
    }
    cout<<g.maxFlow(0,v-1)<<endl;
    return 0;
}
*/

//verify for minCostFlow AOJ(GRL_6_B)
/*
int main(){
    int V,E,F;
    cin>>V>>E>>F;
    Flow g(V);
    for(int i=0;i<E;i++){
        int u,v,c,d;
        cin>>u>>v>>c>>d;
        g.addEdge(u,v,c,d);
    }
    cout<<g.minCostFlow(0,V-1,F)<<endl;
    return 0;
}
*/