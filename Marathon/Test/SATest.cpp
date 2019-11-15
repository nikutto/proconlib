#include"Manager.cpp"
#include"../SA.cpp"

using namespace ProconLib;

class TempManager{
    using score_t = int;
    public:
    using temp_t = double;
    private:
    const temp_t startTemp = 40 ,endTemp = 2;
    public:
    temp_t getTemperature(myTime_t t,myTime_t limit){return startTemp + (endTemp - startTemp) * t / limit;}
    double getProbability(score_t score,score_t newScore,temp_t temp){return exp((newScore-score)/temp);}
};


int main(){
    vector<int> B(3);
    cin>>N>>B[0]>>B[1]>>B[2];
    Field l,r;
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
    SimulatedAnnealing<Manager,TempManager> sa(manager,TempManager());
    
    auto res = sa(2.9);
    for(int i=0;i<10;i++) res=manager.initialState(N,res);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<res.f[i][j]<<" ";
        }
        cout<<endl;
    }
    cerr<<manager.calcScore(res)<<endl;
    return 0;    
}
