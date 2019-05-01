#include<bits/stdc++.h>
#include"../DisjointSparseTable.cpp"

using namespace std;
using namespace ProconLib;

using ll=long long;

struct OR{
    ll operator()(ll lhs,ll rhs){
        return lhs|rhs;   
    }
};
int main(){
    int n;
    cin>>n;
    ll k;
    cin>>k;
    vector<ll> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    DisjointSparseTable<ll,OR> dst(a);
    ll lb=-1;
    ll ub=1LL<<60;
    auto getR=[&dst,n](int l,ll x){
        int lb=l;
        int ub=n+1;
        while(ub-lb>1){
            int mid=(lb+ub)/2;
            if(dst.query(l,mid)>=x) ub=mid;
            else lb=mid;
        }
        return lb;
    };
    while(ub-lb>1){
        ll mid=(ub+lb)/2;
        ll cnt=0;
        for(int l=0;l<n;l++){
            int r=getR(l,mid);
            cnt+=n-r;
        }
        if(cnt<k) ub=mid;
        else lb=mid;
    }
    cout<<lb<<endl;
    return 0;
}