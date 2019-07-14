#include<bits/stdc++.h>
#include"UnionFind.hpp"
using namespace std;


/*verify(AOJ ALDS1_12_A)
int main(){
    int n;
    cin>>n;
    Graph g(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            Weight c;
            cin>>c;
            if(c==-1) continue;
            g[i].push_back({i,j,c});
        }
    }
    auto mst=MinimumSpanningTree(g);
    cout<<accumulate(mst.begin(),mst.end(),Weight(0),[](const Weight& lhs,const Edge& rhs){return lhs+rhs.weight;})<<endl;
    return 0;
}
*/