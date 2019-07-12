// AOJ(DSL_1_A)
#include<bits/stdc++.h>
#include"../UnionFind.cpp"
using namespace std;
using namespace ProconLib;

int main(){
    int n,q;
    cin>>n>>q;
    UnionFind u(n);
    for(int i=0;i<q;i++){
        int com,x,y;
        cin>>com>>x>>y;
        if(com){
            cout<<u.same(x,y)<<endl;;
        }
        else{
            u.unite(x,y);
        }
    }
    return 0;

}
