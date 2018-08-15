#include<bits/stdc++.h>
using namespace std;

using Data=int;

struct Edge{
    int from,to;   
    Data dat; 
};
using Edges=vector<Edge>;
using Graph=vector<Edges>;

class LCAQuery{
    static const int SIZE=25;
    vector<vector<int>> par;
    vector<vector<Data>> data;
    vector<int> dep;
    function<Data(Data,Data)> &f;
    Data E;
    void dfs(int v,int pre,int d,Graph& g){
        assert(dep[v]==-1);
        dep[v]=d;
        for(int i=0;i<g[v].size();i++){
            int to=g[v][i].to;
            if(to!=pre){
                data[0][to]=g[v][i].dat;
                par[0][to]=v;
                dfs(to,v,d+1,g);
            }
        }
        return;
    }
    public:
    LCAQuery(int root,function<Data(Data,Data)>& merge,Data e,Graph &g):dep(g.size(),-1),par(SIZE,vector<int>(g.size(),0)),f(merge),E(e){
        int n=g.size();
        dfs(root,root,0,g);
        par[0][root]=root;
        data[0][root]=e;
        for(int i=0;i+1<SIZE;i++){
            for(int j=0;j<n;j++){
                par[i+1][j]=par[i][par[i][j]];
                data[i+1][j]=merge(data[i][par[i][j]],data[i][j]);
            }
        }
    }

    pair<int,pair<Data,Data>> query(int a,int b){
        bool isSwap=(dep[a]>dep[b]);
        if(isSwap){
            swap(a,b);
        }
        Data resa=E;
        Data resb=E;
        int climb=dep[b]-dep[a];
        for(int i=0;i<SIZE;i++){
            if((climb>>i)&1){
                resa=f(resa,data[i][a]);
                a=par[i][a];
            }
        }
        if(a==b){
            if(isSwap){
                return make_pair(a,make_pair(resb,resa));
            }
            else{
                return make_pair(a,make_pair(resa,resb));
            }
        }
        for(int i=SIZE-1;i>=0;i--){
            if(par[i][a]!=par[i][b]){
                resa=f(resa,data[i][a]);
                resb=f(resb,data[i][b]);
                a=par[i][a];
                b=par[i][b];
            }
        }
        resa=f(resa,data[0][a]);
        resb=f(resb,data[0][b]);
        a=par[0][a];
        b=par[0][b];
        assert(a==b);
        if(isSwap) return make_pair(a,make_pair(resb,resa));
        return make_pair(a,make_pair(resa,resb));
    }
};