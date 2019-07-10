// verify for maxFlow AOJ(GRL_6_A)
#include"../MaximumFlow.cpp"
#include<bits/stdc++.h>
using namespace ProconLib;
int main(){
    int v,e;
    std::cin>>v>>e;
    MaximumFlow<long long> g(v);
    for(int i=0;i<e;i++){
        int u,v,c;
        std::cin>>u>>v>>c;
        g.addEdge(u,v,c);
    }
    std::cout<<g.maximumFlow(0,v-1)<<std::endl;
    return 0;
}