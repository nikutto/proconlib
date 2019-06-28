#include<bits/stdc++.h>

namespace ProconLib{

    //struct graph_t
    //  requirement
    //      int to;


    template<class graph_t>
    std::vector<int> TopologicalSort(const graph_t &g){
        int n=g.size();
        std::vector<int> res(n);
        std::vector<int> in(n);
        for(int i=0;i<n;i++) for(auto e:g[i]) in[e.to]++;

        std::queue<int> que;
        for(int i=0;i<n;i++) if(in[i]==0) que.push(i);

        int id=0;
        while(!que.empty()){
            int v=que.front(); que.pop();
            res[id++]=v;
            for(auto e:g[v]){
                in[e.to]--;
                if(in[e.to]==0) que.push(e.to);
            }
        }
        if(id!=n){
            throw std::runtime_error("Given graph is not DAG.");
        }
        return res;
    };

    template<typename graph_t>
    bool isDAG(const graph_t& g){
        try{
            TopologicalSort(g);
            return true;
        }catch(std::runtime_error e){
            return false;
        }
    }
    
};

