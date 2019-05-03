// verify(yukicoder No,318)
#include<bits/stdc++.h>
#include"../LazySegmentTree.cpp"
using namespace std;
using namespace ProconLib;

struct MyMUStruct{
    struct Monoid{
        using value_t = int;
        static constexpr value_t E(){return 0;}
        static value_t op(value_t x,value_t y){
            return max(x,y);
        }
    };
    struct Update{
        using update_t = int;
        static update_t op(update_t x,update_t y){
            return y;
        }
    };
    static typename Monoid::value_t evaluate(Monoid::value_t x,Update::update_t y){
        return y;
    }
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];

    map<int,vector<int>> mp;
    for(int i=0;i<n;i++) mp[a[i]].push_back(i);
    LazySegmentTree<MyMUStruct> seg(n);
    
    for(auto &e:mp){
        int tar=e.first;
        vector<int>& vec=e.second;
        if(vec.empty()) continue;
        seg.apply(vec[0],vec.back()+1,tar);
    }
    
    vector<int> b(n);
    for(int i=0;i<n;i++) b[i]=seg.query(i,i+1);
    for(int i=0;i<n;i++){
        cout<<b[i]<<(i+1==n ? "\n" : " ");
    }
    return 0;
}
