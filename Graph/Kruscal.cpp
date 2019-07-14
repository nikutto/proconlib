#include<algorithm>
#include<vector>
#include"../DataStructure/UnionFind.cpp"

namespace ProconLib{
    template<typename weight_t,class edge_t>
    weight_t Kruscal(int N,std::vector<edge_t>& edges){
        std::sort(edges.begin(),edges.end(),[&](const edge_t& lhs,const edge_t& rhs){return lhs.weight<rhs.weight;});
        weight_t res=0;
        UnionFind u(N);
        for(auto& e:edges){
            if(!u.same(e.from,e.to)){
                res+=e.weight;
                u.unite(e.from,e.to);
            }
        }
        return res;
    }  
}