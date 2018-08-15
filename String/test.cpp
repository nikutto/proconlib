#include<bits/stdc++.h>
using namespace std;

class myclass{
    const int x;

    public:
    myclass(int x):x(x){
        return;
    }
    void showX(){
        cout<<x<<endl;
    }
};

int main(){
    int x;
    cin>>x;
    myclass mc(x);
    mc.showX();
    return 0;
}