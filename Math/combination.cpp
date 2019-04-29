#include<bits/stdc++.h>

namespace ProconLib{

    template<typename MInt>
    class ModCombination{
        int N;
        std::vector<MInt> fact;
        std::vector<MInt> factInv;
        public:
        ModCombination(int n);
        F(int n){return fact[n];}
        FI(int n){return factInv[n];}
        P(int n,int k){return fact[n]*factInv[n-k];}
        PI(int n,int k){return factInv[n]*fact[n-k];}
        C(int n,int k){return fact[n]*factInv[k]*factInv[n-k];}
        CI(int n,int k){return factInv[n]*fact[k]*fact[n-k];}
    };

    template<typename MInt>
    ModCombination<MInt>::ModCombination(int n):N(n),fact(n+1),factInv(n+1){
        fact[0]=MInt(1);
        for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i;
        factInv[n]=inv(fact[n]);
        for(int i=n-1;i>=0;i--){
            factInv[i]=factInv[i+1]*(i+1);
        }
    }
    
}