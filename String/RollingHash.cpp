#include<bits/stdc++.h>

namespace ProconLib{
    using Hash=__int128;
    template<typename Container>
    class RollingHash{
        int N;
        const static Hash MOD=Hash(1e18l)+9;
        const static Hash A=Hash(1e12l)+39;
        std::vector<Hash> powA;
        std::vector<Hash> h;
        public:
        RollingHash(Container c):N(c.size()),h(N+1,0),powA(N+1){
            int id=0;
            for(auto e:c){
                h[id+1]=((h[id]*A+e)%MOD);
                id++;
            }
            powA[0]=1;
            for(int i=0;i+1<=N;i++) powA[i+1]=(powA[i]*A)%MOD;
        }
        Hash get(int l,int r){
            return (h[r]+(MOD-(h[l]*powA[r-l])%MOD))%MOD;
        }
        Hash getA(){return A;}
        Hash getMOD(){return MOD;}
    };
};

//not verified
