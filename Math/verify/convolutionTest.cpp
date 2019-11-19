#include<bits/stdc++.h>
using namespace std;
#include"../convolution.cpp"

int main(){
    int N;
    cin>>N;
    vector<double> A(N+1),B(N+1);
    for(int i=0;i<N;i++) cin>>A[i+1]>>B[i+1];

    auto C=convolution(A,B);
    for(int i=1;i<C.size();i++) cout<<(int)(round(C[i]))<<endl;

    return 0;
}
