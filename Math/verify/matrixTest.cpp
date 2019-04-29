#include<bits/stdc++.h>
#include"../matrix.cpp"
using namespace std;

using namespace ProconLib;
using ld=double;
int main(){
    int s,n,k;
    cin>>s>>n>>k;
    if(n==1){
        cout<<(s%k==0 ? abs(s)/k : -1)<<endl;
        return 0;
    }
    
    int sz=n*k+1;
    
    vector<vector<ld>> dp(k+1,vector<ld>(sz));
    dp[0][0]=1;
    for(int i=0;i<k;i++){
        for(int j=0;j<sz;j++){
            for(int k=1;k<=n;k++){
                if(j+k<sz) dp[i+1][j+k]+=dp[i][j]/n;
            }
        }
    }
    
    Matrix<ld> B(sz,sz+1);
    {
        B[0][0]=1;
        B[0][sz]=0;
        for(int i=1;i<sz;i++){
            B[i][i]=-1;
            for(int j=0;j<sz;j++){
                // i to j
                int d=i-j;
                if(0<=d && d<sz){
                    B[i][j]+=dp[k][d];
                    B[i][sz]-=dp[k][d];
                }
                d=i+j;
                if(j!=0 && 0<=d && d<sz){
                    B[i][j]+=dp[k][d];
                    B[i][sz]-=dp[k][d];
                }
            }
        }
    }
    B=gaussianElimination(B);
    Vector<ld> vec(sz+1);
    for(int i=sz-1;i>=0;i--){
        for(int j=0;j<i;j++){
            B[j][sz]-=B[j][i]/B[i][i]*B[i][sz];
            B[j][i]=0;
        }
    }
    for(int i=0;i<sz;i++){
        vec[sz-i-1]=B[i][sz]/B[i][i];
    }
    vec[sz]=1;

    Matrix<ld> A(sz+1,sz+1);
    for(int i=1;i<sz;i++){
        A[i][i-1]=1;
    }
    A[sz][sz]=1;
    for(int i=0;i<sz;i++){
        int d=i+1;
        if(d<sz) A[0][i]=dp[k][d];
        if(d<sz) A[0][sz]+=dp[k][d];
    }
    A=pow(A,abs(s));
    ld res=(A*vec)[sz-1];
    cout<<fixed<<setprecision(10);
    cout<<res<<endl;

    return 0;
}