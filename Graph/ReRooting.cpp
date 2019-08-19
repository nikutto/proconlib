#include<vector>
#include<iostream>
namespace ProconLib{

    template<typename edge_t>
    class StructInterface{
        struct data_t;    
        struct value_t;
        data_t E();
        data_t merge(data_t x,data_t y);
        data_t mergeV(data_t x,int v);
        data_t mergeE(data_t x,const edge_t& e);
        value_t solve(int v,const std::vector<data_t>& vec);
    };

    template<class graph_t,class Struct>
    class ReRooting{
        int N;
        int root;
        Struct st;
        using data_t=typename Struct::data_t;
        using value_t=typename Struct::value_t;
        std::vector<data_t> dp;
        std::vector<value_t> res;
        void dfs0(int v,int pre,const graph_t& g);
        void dfs1(int v,int pre,data_t dPar,const graph_t& g);
        public:
        ReRooting(const graph_t& graph,Struct st=Struct(),int root=0);
        std::vector<value_t> get(){return res;};
    };

    template<class graph_t,class Struct>
    ReRooting<graph_t,Struct>::ReRooting(const graph_t& g,Struct st,int root)
        :N(g.size()),root(root),st(st),dp(N),res(N)
    {
        dfs0(root,-1,g);
        dfs1(root,-1,data_t(),g);
    }

    template<class graph_t,class Struct>
    void ReRooting<graph_t,Struct>::dfs0(int v,int pre,const graph_t& g){
        dp[v]=st.E();
        for(auto &e:g[v]){
            if(e.to==pre) continue;
            dfs0(e.to,v,g);
            dp[v]=st.merge(dp[v],st.mergeE(dp[e.to],e));
        }
        dp[v]=st.mergeV(dp[v],v);
    }
    
    template<class graph_t,class Struct>
    void ReRooting<graph_t,Struct>::dfs1(int v,int pre,data_t dPar,const graph_t& g){
        std::vector<data_t> tmp;
        tmp.reserve(g[v].size());
        for(auto &e:g[v]) if(e.to!=pre) tmp.push_back(st.mergeE(dp[e.to],e));
        int sz=tmp.size();
        std::vector<data_t> rsum(sz+1);
        rsum[sz]=st.E();
        for(int i=sz-1;i>=0;i--) rsum[i]=st.merge(rsum[i+1],tmp[i]);

        data_t lsum=st.E();
        int id=0;
        for(auto &e:g[v]){
            if(e.to==pre) continue;
            data_t cdsum=st.merge(st.merge(lsum,rsum[id+1]),dPar);
            data_t nextDPar=st.mergeE(st.mergeV(cdsum,v),e);
            dfs1(e.to,v,nextDPar,g);
            lsum=st.merge(lsum,tmp[id]);
            id++;
        }

        if(v!=root) tmp.push_back(dPar);
        res[v]=st.solve(v,tmp);
    }

}