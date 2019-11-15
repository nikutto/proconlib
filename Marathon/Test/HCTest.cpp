#define DEBUG
#include"Manager.cpp"
#include"../HC.cpp"
using namespace ProconLib;

int main(){
    vector<int> B(3);
    cin>>N>>B[0]>>B[1]>>B[2];
    Field l(N,Row(N)),r(N,Row(N));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>l[i][j];
        }
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>r[i][j],r[i][j]++;
        }
    }
    Manager manager(B,l,r);
    HillClimbing<Manager> hc(manager);
    
    auto res = hc(2.8);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<res.f[i][j]<<" ";
        }
        cout<<endl;
    }
    cerr<<manager.calcScore(res)<<endl;
    return 0;    
}
