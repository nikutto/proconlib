
namespace ProconLib{

    template<typename Int>
    Int extGCD(Int a,Int b,Int& x,Int& y){
        if(b==0){
            x=Int(1);
            y=Int(0);
            return a;
        }
        else{
            Int g=extGCD(b,a%b,x,y); 
            // translation
            // bx+(a%b)y==g
            // bx+(a-a/b*b)y=g
            // a*y+b*(x-a/b)=g
            Int tmp=x;
            x=y;
            y=tmp-a/b*y;
            return g;
        }
    }
}
#include<bits/stdc++.h>
using namespace std;
using namespace ProconLib;

using ll=long long;
int main(){
    ll a,b; cin>>a>>b;
    ll x,y;
    extGCD(a,b,x,y);
    cout<<x<<" "<<y<<endl;
    return 0;
}
