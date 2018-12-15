#include<bits/stdc++.h>
using namespace std;
using Weight=long long;

struct Edge{
    int to;
    Weight weight;
};
using Edges=vector<Edge>;
using Graph=vector<Edges>;

Weight INF=1e9+7;
vector<Weight> Dijkstra(int s,const Graph& g){
    int n=g.size();
    vector<Weight> res(n,INF);
    vector<int> used(n,0);
    res[s]=0;
    priority_queue<pair<Weight,int>,vector<pair<Weight,int>>,greater<>> que;
    que.push(make_pair(Weight(0),s));
    while(!que.empty()){
        auto p=que.top(); que.pop();
        Weight dist=p.first;
        int v=p.second;
        if(used[v]) continue;
        used[v]=true;
        for(int i=0;i<g[v].size();i++){
            Weight tdist=dist+g[v][i].weight;
            if(tdist<res[g[v][i].to]){
                res[g[v][i].to]=tdist;
                que.push(make_pair(tdist,g[v][i].to));
            }
        }
    }
    return res;
}

/* AOJ(ALDS1_12_C)
int main(){
    int n;
    cin>>n;
    Graph g(n);
    for(int i=0;i<n;i++){
        int u,k;
        cin>>u>>k;
        for(int j=0;j<k;j++){
            Edge e;
            cin>>e.to>>e.weight;
            g[u].push_back(e);
        }
    }
    auto d=Dijkstra(0,g);
    for(int i=0;i<n;i++){
        cout<<i<<" "<<d[i]<<endl;
    }

    return 0;
}
*/