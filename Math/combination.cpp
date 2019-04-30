#include<bits/stdc++.h>

namespace ProconLib{

    template<typename MInt>
    class ModCombination{
        int N;
        std::vector<MInt> fact;
        std::vector<MInt> factInv;
        public:
        ModCombination(int n);
        MInt F(int n){return fact[n];}
        MInt FI(int n){return factInv[n];}
        MInt P(int n,int k){return fact[n]*factInv[n-k];}
        MInt PI(int n,int k){return factInv[n]*fact[n-k];}
        MInt C(int n,int k){return fact[n]*factInv[k]*factInv[n-k];}
        MInt CI(int n,int k){return factInv[n]*fact[k]*fact[n-k];}
    };

    template<typename MInt>
    ModCombination<MInt>::ModCombination(int n):N(n),fact(n+1),factInv(n+1){
        fact[0]=MInt(1);
        for(int i=1;i<=n;i++) fact[i]=fact[i-1]*MInt(i);
        factInv[n]=inv(fact[n]);
        for(int i=n-1;i>=0;i--){
            factInv[i]=factInv[i+1]*MInt(i+1);
        }
    }
    
}