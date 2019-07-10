#include<bits/stdc++.h>
using namespace std;
#include"../MinimumCostFlow.cpp"
using namespace ProconLib;
int main(){
    int V,E,F;
    cin>>V>>E>>F;
    MinimumCostFlow<long long> g(V);
    for(int i=0;i<E;i++){
        int u,v,c,d;
        cin>>u>>v>>c>>d;
        g.addEdge(u,v,c,d);
    }
    cout<<g.minimumCostFlow(0,V-1,F)<<endl;
    return 0;
}