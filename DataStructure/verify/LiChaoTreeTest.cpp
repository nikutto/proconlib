#include<bits/stdc++.h>
using namespace std;

#include"../LiChaoTree.cpp"
using namespace ProconLib;
using ll=long long;
const int lb=-4;
const int ub=4;

using Option=IntOption<less<ll>>;
int main(){
    LiChaoTree<ll,Option> cht(lb,ub);
    int type;
    while(cin>>type,type){
        if(type==1){
            ll a,b;
            cin>>a>>b;
            cht.add(a,b);
        }
        else if(type==2){
           ll x;
            cin>>x;
            cout<<cht.get(x)<<endl;
        }
    }    
    return 0;
}