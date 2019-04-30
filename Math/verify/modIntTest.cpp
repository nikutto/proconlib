//verify(https://atcoder.jp/contests/exawizards2019/tasks/exawizards2019_e)

#include<bits/stdc++.h>
#include"../modInt.cpp"
#include"../combination.cpp"
using namespace std;
using namespace ProconLib;

const int MOD=1e9+7;
using mint=ModInt<MOD,true>;
int main(){
    int b,w;
    cin>>b>>w;
    vector<mint> res(b+w);
    vector<mint> v(b+w);
    mint ext=0;
    ModCombination<mint> comb(b+w+1);
    for(int i=0;i<b+w;i++){
        if(i==0){
            v[i]=1;
        }
        else{
            int x=max(i-w+1,0);
            int y=min(i,b-1);
            bool xb=(x!=0);
            bool yb=(y!=i);
            v[i]=v[i-1]*2;
            if(xb) v[i]-=comb.C(i-1,x-1);
            if(yb) v[i]-=comb.C(i-1,b-1);
        }
        mint lv=powm(inv(mint(2)),i+1)*v[i];
        res[i]=lv+ext;
        if(i>=w-1) ext+=powm(inv(mint(2)),i+1)*comb.C(i,w-1);
    }
    for(int i=0;i<b+w;i++){
        cout<<res[i]<<endl;
    }
    return 0;
}