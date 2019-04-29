#include<bits/stdc++.h>
using namespace std;

using Hash=__int128;

class RollingHash{
    map<char,Hash> dic; //hashed by B,C,MOD
    Hash MOD;
    vector<Hash> h;//hash(s[0,i))
    //hash(str)=sigma(dic[str[len(str)-i-1]]*A^(i))%MOD
    const Hash A,B,C;
    const static Hash DEF_A=1000000009;
    const static Hash DEF_B=123456729;
    const static Hash DEF_C=3000000019;
    
    vector<Hash> Apow;
    void setDict(Hash B,Hash C,Hash MOD){
        dic['a']=B;
        for(char c='b';c<='z';c++){
            dic[c]=((dic[c-1]*B)%MOD+C)%MOD;
        }
    }
    public:
    RollingHash(string& s,Hash A,Hash B,Hash C,Hash MOD):h(s.size()+1),Apow(s.size()+1),A(A),B(B),C(C),MOD(MOD){
        setDict(B,C,MOD);
        h[0]=0;
        Apow[0]=1;
        for(int i=0;i<s.size();i++){
            Apow[i+1]=(Apow[i]*A)%MOD;
        }
        for(int i=0;i<s.size();i++){
            h[i+1]=((h[i]*A)%MOD+dic[s[i]])%MOD;
        }
        return;
    }
    RollingHash(string& s):h(s.size()+1),Apow(s.size()+1),A(DEF_A),B(DEF_B),C(DEF_C){
        setDict(B,C,MOD);
        h[0]=0;
        Apow[0]=1;
        for(int i=0;i<s.size();i++){
            Apow[i+1]=(Apow[i]*A)%MOD;
        }
        for(int i=0;i<s.size();i++){
            h[i+1]=((h[i]*A)%MOD+dic[s[i]])%MOD;
        }
        return;
    }
    Hash dict(char x) const{
        return dic.at(x);
    }
    Hash getHash(int l,int r){
        assert(l<=r);
        return ((h[r]-(h[l]*Apow[r-l])%MOD)+MOD)%MOD;
    }
};
