// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2212
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#include"../AhoCorasick.cpp"
using namespace ProconLib;
using Field=vector<string>;

using vi=vector<int>;
using vvi=vector<vi>;
using vvvi=vector<vvi>;

int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
char dc[]={'d','r','u','l'};

int solve(int h,int w){
    Field f(h);
    for(int i=0;i<h;i++) cin>>f[i];

    auto isRange=[&](int i,int j){
        return 0<=i && i<h && 0<=j && j<w;
    };

    int k;
    cin>>k;
    vector<string> pat(k);
    for(int i=0;i<k;i++) cin>>pat[i];
    for(int i=0;i<k;i++) for(char& x:pat[i]) x=tolower(x);
    AhoCorasick<LowerCase> ac(pat);
    int n=ac.size();
    

    auto isValid=[&](int x,int y,int st){
        int v=ac.accept(st);
        return isRange(x,y) && f[x][y]!='#' && v==ac.rejectToken();
    
    };
    const int INF=1e9;
    vvvi dp(h,vvi(w,vi(n,INF)));

    struct X{
        int x,y;
        int st;
    };
    queue<X> que;
    pair<int,int> gpos;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(f[i][j]=='S'){
                dp[i][j][0]=0;
                que.push(X{i,j,0});
            }
            if(f[i][j]=='G'){
                gpos.first=i;
                gpos.second=j;
            }

        }
    }
    
    while(!que.empty()){
        X tmp=que.front(); que.pop();
        for(int i=0;i<4;i++){
            X tox={tmp.x+dx[i],tmp.y+dy[i],ac.next(tmp.st,dc[i])};
            if(isValid(tox.x,tox.y,tox.st) && dp[tox.x][tox.y][tox.st]==INF){
                dp[tox.x][tox.y][tox.st]=dp[tmp.x][tmp.y][tmp.st]+1;
                que.push(tox);
            }
        }
    }
    int res=INF;
    for(int i=0;i<n;i++){
        res=min(res,dp[gpos.first][gpos.second][i]);
    }
    cout<<(res<INF ? res: -1)<<endl;

    
    return 0;
}

int main(){
    int h,w;
    while(cin>>h>>w,h){
        solve(h,w);
    }
    return 0;
}