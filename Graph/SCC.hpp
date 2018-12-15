#include<bits/stdc++.h>


namespace ProconLib{

    template<typename graph_t>
    class SCC{  
        std::vector<int> vs;
        std::vector<int> used;
        void dfs(int v,const graph_t& g);
        void rdfs(int v,int k,std::vector<std::vector<int>>& rg);
        int k;
        std::vector<int> cmp;
        public:
        SCC(const graph_t& g);
        int getK(){return k;}
        std::vector<int> getCmp(){return cmp;}
    };

    template<typename graph_t>
    SCC<graph_t>::SCC(const graph_t& g):used(g.size(),false){
        int n=g.size();
        std::vector<std::vector<int>> rg(n);
        for(int i=0;i<n;i++) for(auto &e:g[i]) rg[e.to].push_back(i);
        for(int i=0;i<n;i++) dfs(i,g);
        fill(begin(used),end(used),0);
        cmp.assign(n,-1);
        int k=0;
        for(int i=n-1;i>=0;i--) if(!used[vs[i]]) rdfs(vs[i],k++,rg);
    }

    template<typename graph_t>
    void SCC<graph_t>::dfs(int v,const graph_t& g){
        if(used[v]) return;
        used[v]=true;
        for(auto& e:g[v]) dfs(e.to,g);
        vs.push_back(v);
        return;
    }

    template<typename graph_t>
    void SCC<graph_t>::rdfs(int v,int k,std::vector<std::vector<int>>& rg){
        if(used[v]) return;
        used[v]=true;
        cmp[v]=k;
        for(int i=0;i<rg[v].size();i++) rdfs(rg[v][i],k,rg);
    }

    template<typename graph_t>
    std::vector<std::vector<int>> shrink(const graph_t& g,int k,const std::vector<int>& cmp){
        int n=g.size();
        std::vector<std::set<int>> sg(k);
        for(int i=0;i<n;i++){
            for(int j=0;j<g[i].size();j++) sg[cmp[i]].insert(cmp[g[i][j].to]);
        }
        std::vector<std::vector<int>> res(k);
        for(int i=0;i<k;i++){
            for(auto e:sg[i]) res[i].push_back(e);
        }
        return res;
    }

}