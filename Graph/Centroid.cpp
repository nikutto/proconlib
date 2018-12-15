#include<bits/stdc++.h>
using namespace std;
using Graph=vector<vector<int>>;

class Centroid{
    vector<int> sz;
    int setSZ(int v,int pre,const Graph& g){
        int res=0;
        for(int i=0;i<g[v].size();i++){
            if(g[v][i]!=pre) res+=setSZ(g[v][i],v,g);
        }
        return sz[v]=res+1;
    }
    int dfs(int v,int pre,int n,const Graph& g){
        int maxSize=n-sz[v];
        for(int i=0;i<g[v].size();i++){
            if(g[v][i]!=pre) maxSize=max(maxSize,sz[g[v][i]]);
        }
        if(maxSize<=n/2) return v;
        for(int i=0;i<g[v].size();i++){
            if(pre!=g[v][i]){
                int ret=dfs(g[v][i],v,n,g);
                if(ret!=-1) return ret;
            }
        }
        return -1;
    }
    public:
    Centroid(int n){
        sz.assign(n,-1);
    }
    int operator()(int v,const Graph& g){    
        int n=setSZ(v,-1,g);
        int ret=dfs(v,-1,n,g);
        assert(ret>=0);
        return ret;
    }
};

/* verify(Codeforces Round #190 (Div. 1)) ProblemC: Ciel the Commander
int main(){
    int n;
    cin>>n;
    Centroid cent(n);
    Graph g(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> ans(n,-1);
    queue<pair<int,int>> que;
    que.push(make_pair(0,0));
    while(!que.empty()){
        auto ret=que.front(); que.pop();
        int v=ret.first;
        v=cent(v,g);
        int val=ret.second;
        ans[v]=val;
        for(int i=0;i<g[v].size();i++){
            int to=g[v][i];
            g[to].erase(find(g[to].begin(),g[to].end(),v));
            que.push(make_pair(to,val+1));
        }
    }
    vector<char> str(n);
    for(int i=0;i<n;i++){
        if(ans[i]>'z'-'a'){
            cout<<"Impossible!"<<endl;
        }
        else{
            str[i]=ans[i]+'A';
        }
    }
    for(int i=0;i<n;i++) cout<<str[i]<<(i==n-1 ? "\n" : " ");
    return 0;
}
*/