#include<cmath>
#include<vector>
#include<cassert>
namespace ProconLib{

    template<class graph_t>
    class LCA{
        private:        
        static int safeLog2(int N){return std::ceil(std::log2(N+1))+1;}
        void dfs(int v,int pre,const graph_t& g);

        protected:
        int N;
        int logN;
        std::vector<std::vector<int>> par;
        std::vector<int> dep;

        public:
        LCA(int root,const graph_t &g);
        int query(int a,int b);
        int depth(int v){return dep[v];}
    };

    template<class graph_t>
    void LCA<graph_t>::dfs(int v,int pre,const graph_t& g){
        par[0][v]=pre;
        for(auto e:g[v]){
            if(e.to==pre) continue;
            par[0][e.to]=v;
            dep[e.to]=dep[v]+1;
            dfs(e.to,v,g);
        }
    }

    template<class graph_t>
    LCA<graph_t>::LCA(int root,const graph_t &g): N(g.size()),
                                        logN(safeLog2(N)),
                                        par(logN,std::vector<int>(N)),
                                        dep(N)
    {
        par[0][root]=root;
        dep[root]=0;
        dfs(root,root,g);
        for(int i=0;i+1<logN;i++){
            for(int j=0;j<N;j++){
                par[i+1][j]=par[i][par[i][j]];
            }
        }
    }

    template<class graph_t>
    int LCA<graph_t>::query(int a,int b){
        if(dep[a]<dep[b]) std::swap(a,b);
        int u=dep[a]-dep[b];
        for(int i=logN-1;i>=0;i--){
            if((u>>i)&1) a=par[i][a];
        }
        assert(dep[a]==dep[b]);
        if(a==b) return a;
        for(int i=logN-1;i>=0;i--){
            if(par[i][a]!=par[i][b]){
                a=par[i][a];
                b=par[i][b];
            }
        }
        assert(a!=b);
        a=par[0][a],b=par[0][b];
        assert(a==b);
        return a;
    }
    
}