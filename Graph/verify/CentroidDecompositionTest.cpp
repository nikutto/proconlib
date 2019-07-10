//AtCoder みんぷろ本選2018 C-木の問題
#include<bits/stdc++.h>
#include"../CentroidDecomposition.cpp"
using namespace std;
using namespace ProconLib;

struct Edge{
    int to;
};
using Edges=vector<Edge>;
using Graph=vector<Edges>;

struct Query{
    int id,v,k;
};
struct Solver{
    vector<int> ans;
    vector<int> dep;
    vector<vector<Query>> vqs;
    int maxDep;
    void setDepth(int v,int pre,Graph& g,vector<int>& used){
        for(auto& e:g[v]){
            if(e.to==pre || used[e.to]) continue;
            dep[e.to]=dep[v]+1;
            setDepth(e.to,v,g,used);
            maxDep=max(maxDep,dep[v]+1);
        }
    }
    void dfs(int v,int pre,Graph& g,vector<int>& used,vector<int>& vec,vector<Query>& qs){
        while(vec.size()<=dep[v]) vec.push_back(0);
        vec[dep[v]]++;
        for(auto q:vqs[v]) qs.push_back(q);
        for(auto& e:g[v]){
            if(e.to==pre || used[e.to]) continue;
            dfs(e.to,v,g,used,vec,qs);
        }
    }
    public:
    Solver(int n,int q):dep(n),vqs(n),ans(q){}
    void add(int id,int v,int k){
        vqs[v].push_back(Query{id,v,k});
    }
    void solve(int v,Graph& g,vector<int>& used){
        dep[v]=0;
        maxDep=0;
        setDepth(v,-1,g,used);
        vector<int> depCnt(maxDep+1);
        vector<vector<int>> dvec;
        vector<vector<Query>> qvec;
        for(auto& e:g[v]){
            if(used[e.to]) continue;
            vector<Query> qs;
            vector<int> vec;
            dfs(e.to,v,g,used,vec,qs);
            dvec.push_back(vec);
            qvec.push_back(qs);
            for(int i=0;i<vec.size();i++){
                depCnt[i]+=vec[i];
            }
        }
        depCnt[0]=1;
        int sz=dvec.size();
        for(int i=0;i<sz;i++){
            for(auto q:qvec[i]){
                int v=q.v;
                int tar=q.k-dep[v];
                if(tar>maxDep|| tar<0) continue;
                int dec=(tar<dvec[i].size() ? dvec[i][tar] : 0);
                ans[q.id]+=depCnt[tar]-dec;
            }
        }
        for(auto q:vqs[v]){
            if(q.k<=maxDep) ans[q.id]+=depCnt[q.k];
        }
        return;
    }
    void printAns(){
        for(int i=0;i<ans.size();i++) cout<<ans[i]<<endl;
    } 
};
int main(){
    int n,q;
    cin>>n>>q;
    Graph g(n);
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        a--,b--;
        g[a].push_back({b});
        g[b].push_back({a});
    }
    Solver solver(n,q);
    for(int i=0;i<q;i++){
        int v,k; cin>>v>>k;
        v--;
        solver.add(i,v,k);
    }
    CDRunner<Graph> runner;
    runner.run(g,solver);
    solver.printAns();
    return 0;
}