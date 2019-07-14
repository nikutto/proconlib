#include<bits/stdc++.h>
#include"../Kruscal.cpp"
using namespace std;
using namespace ProconLib;

struct Edge{
    int from,to;
    int weight;
};
using Edges=vector<Edge>;
const int SIZE=50;
int main(){
    int v,e;
    cin>>v>>e;
    Edges edges(e);
    for(int i=0;i<e;i++){
        int s,t,w;
        cin>>s>>t>>w;
        edges[i]=Edge{s,t,w};
    }
    int res=0;
    for(int i=0;i<SIZE;i++){
        res=Kruscal<int>(v,edges);
    }
    cout<<res<<endl;
    return 0;
}