#include<vector>

namespace ProconLib{

    template<class graph_t>
    class EulerTour{
        private:
        int N;
        std::vector<int> ins;
        std::vector<int> outs;
        void dfs(int v,int pre,const graph_t& g,int& id);

        public:
        EulerTour(int root,const graph_t& g);
        int in(int v){return ins[v];}
        int out(int v){return outs[v];}
    };

    template<class graph_t>
    EulerTour<graph_t>::EulerTour(int root,const graph_t& g):N(g.size()),
                                                      ins(N),
                                                        outs(N)
    {   
        int id=0;
        dfs(root,-1,g,id);
    }   

    template<class graph_t>
    void EulerTour<graph_t>::dfs(int v,int pre,const graph_t& g,int& id){
        ins[v]=id++;
        for(auto& e:g[v]){
            if(e.to==pre) continue;
            dfs(e.to,v,g,id);
        }
        outs[v]=id++;
    }
}