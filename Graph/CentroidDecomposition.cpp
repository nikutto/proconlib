#include<bits/stdc++.h>
using namespace std;

struct Edge{
    int from,to;
};
using Edges=vector<Edge>;
using Graph=vector<Edges>;

namespace ProconLib{
    struct Centroid{
        int par;
        vector<int> chil;
    };
    class CentroidDecomposition{
        int root;
        vector<Centroid> cent;
        vector<int> sz;
        vector<int> isCent;
        int setSZ(int v,int pre,const Graph& g){
            sz[v]=1;
            for(int i=0;i<g[v].size();i++){
                if(isCent[g[v][i].to] || g[v][i].to==pre) continue;
                sz[v]+=setSZ(g[v][i].to,v,g);
            }
            return sz[v];
        }
        int findCent(int v,int pre,int size,const Graph &g){
            int maxSize=size-sz[v];
            for(int i=0;i<g[v].size();i++){
                if(isCent[g[v][i].to] || g[v][i].to==pre) continue;
                maxSize=max(maxSize,sz[g[v][i].to]);
            }
            if(maxSize<=size/2) return v;
            for(int i=0;i<g[v].size();i++){
                if(isCent[g[v][i].to] || g[v][i].to==pre) continue;
                int ret=findCent(g[v][i].to,v,size,g);
                if(ret!=-1) return ret;
            }
            return -1;
        }
        int getDist(int v,int pre,int tar,const Graph& g){
            for(int i=0;i<g[v].size();i++){
                if(g[v][i].to==pre) continue;
                if(g[v][i].to==tar) return 1;
                if(isCent[g[v][i].to]) continue;
                int ret=getDist(g[v][i].to,v,tar,g);
                if(ret!=-1){
                    return ret+1;
                }
            }
            return -1;
        }
        int build(int v,int preC,const Graph& g){
            setSZ(v,-1,g);
            v=findCent(v,-1,sz[v],g);
            cent[v].par=preC;
            isCent[v]=true;
            for(int i=0;i<g[v].size();i++){
                if(isCent[g[v][i].to]) continue;
                cent[v].chil.push_back(build(g[v][i].to,v,g));
            }
            return v;
        }
        public:
        CentroidDecomposition(const Graph& g){
            int n=g.size();
            sz.assign(n,0);
            cent.assign(n,Centroid());
            isCent.assign(n,false);
            root=build(0,-1,g);
        }
        int getRoot(){return root;}
        vector<vector<int>> getGraph(){
            vector<vector<int>> res(cent.size());
            for(int i=0;i<cent.size();i++){
                res[i]=cent[i].chil;
            }
            return res;
        }
    };

    struct Query{
        int idx;
        int v;
        int k;
        int ans;
    };
    template<typename Query_t>
    struct TemplateSolver{
        int N;
        Graph g;
        int root;
        vector<vector<int>> cd;
        vector<int> used;
        vector<int> pos;
        vector<vector<int>> qidx;
        //rewrite here
        void dfs(int v,int pre,int k,vector<int>& vs){
            vs.push_back(v);
            pos[v]=k;
            

            for(auto e:g[v]){
                if(e.to==pre || used[e.to]) continue;
                dfs(e.to,v,k,qis);
            }
        }
        void solve(int v,vector<Query_t>& query){
            int k=0;
            pos[v]=-1;
            vector<int> sum(1,1);
            vector<int> vs;
            vs.push_back(v);
            for(auto e:g[v]){
                if(used[e.to]) continue;
                dfs(e.to,v,k,vs);
                k++;
            }
            vector<int> qis;
            for(auto x:vs) for(auto idx:qidx[x]) qis.push_back(idx);

            for(auto idx:qis){
                //update query[idx].ans
                //rewrite here
            }
            used[v]=true;
            for(auto to:cd[v]){
                solve(to,query);
            }
        }
        public:
        TemplateSolver(const Graph &g):N(g.size()),g(g),used(N,false),qidx(N),pos(N){
            CentroidDecomposition cent(g);
            root=cent.getRoot();
            cd=cent.getGraph();
        }
        void solve(vector<Query_t> &query){
            for(int i=0;i<query.size();i++) qidx[query[i].v].push_back(i);
            solve(root,query);
        }
    };

    
}

//AtCoder みんぷろ本選2018 C-木の問題
/*
using namespace ProconLib;
struct Query{
    int idx;
    int v;
    int k;
    int ans;
};

struct Solver{
    int N;
    Graph g;
    vector<vector<int>> cd;
    vector<int> used;
    int root;
    vector<int> pos;
    vector<int> dep;
    vector<vector<int>> qidx;
    void dfs(int v,int pre,int k,vector<int>& dcnt,vector<int>& qis){
        while(dcnt.size()<=dep[v]) dcnt.push_back(0);
        dcnt[dep[v]]++;
        pos[v]=k;
        for(auto qi:qidx[v]) qis.push_back(qi);
        for(auto e:g[v]){
            if(e.to==pre || used[e.to]) continue;
            dep[e.to]=dep[v]+1;
            dfs(e.to,v,k,dcnt,qis);
        }
    }
    void solve(int v,vector<Query>& query){
        int k=0;
        pos[v]=-1;
        dep[v]=0;
        vector<int> sum(1,1);
        vector<vector<int>> dcnts;
        vector<int> qis;
        for(auto idx:qidx[v]) qis.push_back(idx);
        for(auto e:g[v]){
            if(used[e.to]) continue;
            vector<int> dcnt(1);
            dep[e.to]=1;
            dfs(e.to,v,k,dcnt,qis);
            dcnts.push_back(dcnt);
            while(sum.size()<=dcnt.size()) sum.push_back(0);
            for(int i=0;i<dcnt.size();i++) sum[i]+=dcnt[i];
            k++;
        }
        for(auto idx:qis){
            int x=query[idx].k-dep[query[idx].v];
            if(x<0) continue;
            if(x<sum.size()) query[idx].ans+=sum[x];
            if(v!=query[idx].v && x<dcnts[pos[query[idx].v]].size()) query[idx].ans-=dcnts[pos[query[idx].v]][x];
        }
        used[v]=true;
        for(auto to:cd[v]){
            solve(to,query);
        }
    }
    public:
    Solver(const Graph &g):N(g.size()),g(g),used(N,false),qidx(N),pos(N),dep(N){
        CentroidDecomposition cent(g);
        root=cent.getRoot();
        cd=cent.getGraph();
    }
    void solve(vector<Query> &query){
        for(int i=0;i<query.size();i++) qidx[query[i].v].push_back(i);
        solve(root,query);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    Graph g(n);
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        a--,b--;
        g[a].push_back(Edge{a,b});
        g[b].push_back(Edge{b,a});
    }
    vector<Query> query(q);
    for(int i=0;i<q;i++){
        int v,k;
        cin>>v>>k;
        v--;
        query[i]={i,v,k,0};
    }    
    Solver solver(g);
    solver.solve(query);

    for(int i=0;i<q;i++){
        cout<<query[i].ans<<"\n";
    }
    return 0;
}
*/
