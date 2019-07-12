#include<vector>
#include<numeric>

namespace ProconLib{
    class UnionFind{
        int N;
        std::vector<int> par;
        std::vector<int> rank;
        public:
        UnionFind(int N):N(N),par(N),rank(N,0){std::iota(par.begin(),par.end(),0);}
        int find(int x);
        void unite(int x,int y);
        bool same(int x,int y){return find(x)==find(y);}
    };

    int UnionFind::find(int x){
        if(par[x]==x) return x;
        return par[x]=find(par[x]);
    }
    void UnionFind::unite(int x,int y){
        x=find(x),y=find(y);
        if(x==y) return;
        if(rank[x]>=rank[y]){
            if(rank[x]==rank[y]) rank[x]++;
            par[y]=x;
        }else{
            par[x]=y;
        }
    }
}