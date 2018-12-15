#include<bits/stdc++.h>
using namespace std;

struct Edge{
    int from,to;
};
using Edges=vector<Edge>;
using Graph=vector<Edges>;

struct Centroid{
    int par;
    int dist;
    map<int,int> chil;
    vector<vector<int>> cnt;
    vector<int> sumCnt;
    map<int,int> dep;
};

class CentroidDecomposition{
    vector<Centroid> cent;
    vector<int> sz;
    vector<int> isCent;
    int setSZ(int v,int pre,Graph& g){
        sz[v]=1;
        for(int i=0;i<g[v].size();i++){
            if(isCent[g[v][i].to] || g[v][i].to==pre) continue;
            sz[v]+=setSZ(g[v][i].to,v,g);
        }
        return sz[v];
    }
    int findCent(int v,int pre,int size,Graph &g){
        int maxSize=size-sz[v];
        for(int i=0;i<g[v].size();i++){
            if(isCent[g[v][i].to] || g[v][i].to==pre) continue;
            maxSize=max(maxSize,sz[g[v][i].to]);
        }
        if(maxSize<=(size/2)+1) return v;
        for(int i=0;i<g[v].size();i++){
            if(isCent[g[v][i].to] || g[v][i].to==pre) continue;
            int ret=findCent(g[v][i].to,v,size,g);
            if(ret!=-1) return ret;
        }
        return -1;
    }
    int getDist(int v,int pre,int tar,Graph& g){
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
    
    //hojo function for updateCent
    void setCnt(int v,int pre,int dep,int c,int inde,Graph& g){
        while(cent[c].cnt[inde].size()<=dep) cent[c].cnt[inde].push_back(0);
        cent[c].dep[v]=dep;
        cent[c].cnt[inde][dep]++;
        for(int i=0;i<g[v].size();i++){
            if(isCent[g[v][i].to] || g[v][i].to==pre) continue;
            setCnt(g[v][i].to,v,dep+1,c,inde,g);
        }
    }

    //modify this for application
    void updateCent(int v,int preC,Graph &g){
        cent[v].par=preC;
        /*
        if(preC!=-1) cent[v].dist=getDist(v,-1,preC,g);
        else cent[v].dist=1e8;
        */
        cent[v].dep[v]=0;
        cent[v].cnt.assign(g[v].size(),vector<int>(1,0));
        for(int i=0;i<g[v].size();i++){
            if(isCent[g[v][i].to]) continue;
            setCnt(g[v][i].to,v,1,v,i,g);
        }
        int s=0;
        for(int i=0;i<g[v].size();i++){
            s=max(s,int(cent[v].cnt[i].size()));
        }
        cent[v].sumCnt.assign(s,0);
        for(int i=0;i<g[v].size();i++){
            for(int j=0;j<cent[v].cnt[i].size();j++){
                cent[v].sumCnt[j]+=cent[v].cnt[i][j];
            }
        }
    }
    int build(int v,int preC,Graph& g){
        setSZ(v,-1,g);
        v=findCent(v,-1,sz[v],g);
        updateCent(v,preC,g);
        isCent[v]=true;
        for(int i=0;i<g[v].size();i++){
            if(isCent[g[v][i].to]) continue;
            cent[v].chil[build(g[v][i].to,v,g)]=i;
        }
        return v;
    }
    public:
    CentroidDecomposition(Graph& g){
        int n=g.size();
        sz.assign(n,0);
        cent.assign(n,Centroid());
        isCent.assign(n,false);
        build(0,-1,g);
    }
    int query(int v,int pre,int k,int org){
        if(v<0) return 0;
        int prek=k;
        k-=cent[v].dep[org];
        int res=0;
        if(k>0 && cent[v].sumCnt.size()>k){
            res+=cent[v].sumCnt[k];
            if(cent[v].chil.count(pre)){
                int inde=cent[v].chil[pre];
                if(cent[v].cnt[inde].size()>k){
                    res-=cent[v].cnt[inde][k];
                }
            }
        }
        else if(k==0){
            res++;
        }
        return res+query(cent[v].par,v,prek,org);
    }
};

//AtCoder みんぷろ本選2018 C-木の問題
/*
int main(){
    ios_base::sync_with_stdio(false);
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
    
    auto cent=CentroidDecomposition(g);
    while(q--){
        int v,k;
        cin>>v>>k;
        v--;
        cout<<cent.query(v,-1,k,v)<<endl;
    }
    return 0;
}
*/
