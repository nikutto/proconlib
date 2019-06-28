#include<bits/stdc++.h>
using namespace std;

int main(){
    set<int,less<double>> s={0,1,2};
    cout<<*s.lower_bound(0.5)<<endl;
    return 0;
}