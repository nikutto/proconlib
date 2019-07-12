#include<vector>
#include<algorithm>
#include<iostream>
namespace ProconLib{
    
    template<class graph_t>
    class CentroidDecomposition{
        int root;
        std::vector<int> sz;
        std::vector<int> par;
        std::vector<int> isCent;
        int buildDFS(int v,const graph_t& g);
        int szDFS(int v,int pre,const graph_t& g);
        int findCent(int v,int pre,int n,const graph_t& g);
        public:
        CentroidDecomposition(const graph_t& g);
        int getRoot();
        std::vector<int> getPar();
        std::vector<std::vector<int>> getTree();
    };

    template<class graph_t>
    CentroidDecomposition<graph_t>::CentroidDecomposition(const graph_t& g):sz(g.size()),par(g.size()),isCent(g.size()){
        root=buildDFS(0,g);
        par[root]=-1;
    }

    template<class graph_t>
    int CentroidDecomposition<graph_t>::buildDFS(int v,const graph_t& g){
        szDFS(v,-1,g);
        int cent=findCent(v,-1,sz[v],g);
        isCent[cent]=true;
        for(auto& e:g[cent]){
            if(!isCent[e.to]){
                int chil=buildDFS(e.to,g);
                par[chil]=cent;
            }
        }
        return cent;
    }

    template<class graph_t>
    int CentroidDecomposition<graph_t>::szDFS(int v,int pre,const graph_t& g){
        sz[v]=1;
        for(auto& e:g[v]){
            if(e.to==pre || isCent[e.to]) continue;
            sz[v]+=szDFS(e.to,v,g);
        }
        return sz[v];        
    }

    template<class graph_t>
    int CentroidDecomposition<graph_t>::findCent(int v,int pre,int n,const graph_t& g){
        int maxSubSz=n-sz[v];
        for(auto& e:g[v]){
            if(e.to==pre || isCent[e.to]) continue;
            int ret=findCent(e.to,v,n,g);
            if(ret>=0) return ret;
            maxSubSz=std::max(maxSubSz,sz[e.to]);
        }
        if(maxSubSz<=n/2) return v;
        return -1;
   }

    template<class graph_t>
    int CentroidDecomposition<graph_t>::getRoot(){
        return root;
    }

    template<class graph_t>
    std::vector<int> CentroidDecomposition<graph_t>::getPar(){
        return par;
    }

    template<class graph_t>
    std::vector<std::vector<int>> CentroidDecomposition<graph_t>::getTree(){
        std::vector<std::vector<int>> tree(par.size());
        for(int i=0;i<par.size();i++){
            if(par[i]!=-1) tree[par[i]].push_back(i);
        }
        return tree;
    }

    //Centroid Decomposition Solver Runner
    template<class graph_t>
    class CDRunner{
        std::vector<int> used;
        std::vector<std::vector<int>> cdGraph;
        template<class Solver>
        int dfsRun(int v,graph_t& g,Solver& solver);
        public:
        CDRunner(){};

        template<class Solver>
        void run(graph_t& g,Solver& solver);
    };

    template<class graph_t>
    template<class Solver>
    void CDRunner<graph_t>::run(graph_t& g,Solver& solver){
        used.assign(g.size(),0);
        CentroidDecomposition<graph_t> cd(g);
        cdGraph=cd.getTree();
        dfsRun(cd.getRoot(),g,solver);
    }

    template<class graph_t>
    template<class Solver>
    int CDRunner<graph_t>::dfsRun(int v,graph_t& g,Solver& solver){
        solver.solve(v,g,used);
        used[v]=true;
        for(auto to:cdGraph[v]){
            dfsRun(to,g,solver);
        }
    }    
}