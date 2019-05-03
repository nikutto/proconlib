//verify (AOJ 2711 Nearly Clyclic String)
#include<bits/stdc++.h>
#include"../RollingHash.cpp"
#include<bits/stdc++.h>

using namespace std;
using namespace ProconLib;
int main(){
    string s;
    cin>>s;
    int q;
    cin>>q;
    RollingHash<string> rh(s);
    const Hash MOD=rh.getMOD();
    const Hash A=rh.getA();
    vector<Hash> powA(2*1e6);
    powA[0]=1;
    for(int i=0;i+1<powA.size();i++){
        powA[i+1]=powA[i]*A%MOD;
    }
    auto calc=[&](int l,int r,int l1,int r1,int l2,int r2,int t){
        Hash hv=(rh.get(l1,r1)*powA[r2-l2]+rh.get(l2,r2))%MOD;
        vector<Hash> rept(21);
        rept[0]=hv;
        for(int i=0;i<20;i++){
            if((1LL<<i)*t<=s.size()+1) rept[i+1]=(rept[i]*powA[(1LL<<i)*t]+rept[i])%MOD;
        }
        // cerr<<(long long)(rept[1])<<endl;
        // cerr<<(long long)(rh.get(0,6))<<endl;
        for(int i=20;i>=0;i--){
            long long ub=(1LL<<i)*t+l;
            if(ub>r) continue;
            Hash h=rh.get(l,ub);
            if(h==rept[i]){
                l=ub;
            }
        }
        int lb=l,ub=min(r,l+t)+1;
        while(ub-lb>1){
            int mid=(lb+ub)/2;
            int len=mid-l;
            Hash h=0;
            if(r1-l1<len){
                len=mid-l-(r1-l1);
                h=(rh.get(l1,r1)*powA[len]+rh.get(l2,l2+len))%MOD;
            }
            else{
                h=rh.get(l1,l1+len);
            }
            if(rh.get(l,mid)==h) lb=mid;
            else ub=mid;
        }
        return lb;
    };
    while(q--){
        int l,r,t;
        cin>>l>>r>>t;
        l--;
        int x=calc(l,r,l,l+t,l,l,t);
        x++;
        x=calc(x,r,(x-l)%t+l,l+t,l,(x-l)%t+l,t);
        int y=-1;
        if(l+2*t<=s.size()){
            y=calc(l,r,l+t,l+2*t,l,l,t);
            y++;
            y=calc(y,r,(y-l)%t+l+t,l+2*t,l+t,(y-l)%t+l+t,t);
        }
        cout<<((x>=r || y>=r) ? "Yes" : "No")<<endl;
    }

    return 0;    
}