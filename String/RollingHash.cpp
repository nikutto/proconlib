#include<bits/stdc++.h>

namespace ProconLib{
    using Hash=__int128;
    template<typename T,typename HashF>
    class RollingHash{
        int N;
        const static Hash MOD=Hash(1e18l)+9;
        const static Hash A=Hash(1e12l)+39;
        std::vector<Hash> powA;
        std::vector<Hash> h;
        public:
        RollingHash(const std::vector<T>& xs):N(xs.size()),powA(N+1),h(N+1){
            for(int i=0;i<N;i++) h[i+1]=(h[i]*A+HashF(xs[i]))%MOD;
            powA[0]=1;
            for(int i=0;i+1<N;i++) powA[i+1]=(powA[i]*A)%MOD;
        }
        Hash get(int l,int r){
            return (h[r]+(MOD-(h[l]*powA[r-l])%MOD))%MOD;
        }
        Hash getA(){return A;}
    };
};

//not verified
using namespace ProconLib;
using namespace std;
int main(){

}
