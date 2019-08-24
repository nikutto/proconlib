#include<bits/stdc++.h>
using namespace std;

#include"../BipartiteMatching.cpp"
using namespace ProconLib;
int main(){
    int X,Y,E;
    cin>>X>>Y>>E;
    BipartiteMatching bm(X,Y);
    for(int i=0;i<E;i++){
        int x,y;
        cin>>x>>y;
        bm.addEdge(x,y);
    }

    cout<<bm.match()<<endl;
    
    return 0;
}