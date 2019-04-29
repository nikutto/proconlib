#include<bits/stdc++.h>

namespace ProconLib{
    template<typename Container>
    std::vector<int> MP(const Container& xs){
        int N=xs.size();
        std::vector<int> A(N+1);
        A[0]=-1;
        int j=-1;
        for(int i=0;i<N;i++){
            while(j>=0 && xs[i]!=xs[j]) j=A[j];
            j++;
            A[i+1]=j;
        }
        return A;
    }
}

// exampleCase
// aabaabaaa
// _010123452
using namespace std;
using namespace ProconLib;
int main(){
    string s;
    cin>>s;
    auto x=MP<string>(s);
    for(int i=0;i<=x.size();i++){
        cout<<x[i];
    }
    cout<<endl;
    return 0;
}