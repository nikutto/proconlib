#include<bits/stdc++.h>
using namespace std;

const int CN=30;
using Row=array<int,CN>;
using Field=array<Row,CN>;

int N;

unsigned int randxor()
{
    static unsigned int x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned int t;
    t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
}


class Manager{
    vector<int> B;
    Field l,r;
    public:
    using score_t = int;
    struct State{
        Field f;
        array<int,CN> rs,cs;
        array<int,2> diffX,diffY;
        score_t score = 0;
        State(){for(int i=0;i<CN;i++) rs[i]=cs[i]=0; diffX[0]=diffY[0]=diffX[1]=diffY[1]=-1;}
    };
    Manager(vector<int> B,Field l,Field r):B(B),l(l),r(r){};
    State initialState(int poyo=0,State res=State()){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(!poyo) res.f[i][j]=rand()%(l[i][j]-r[i][j])+l[i][j];;
                if(!poyo && myRand()%8) continue;
                for(int k=l[i][j];k<r[i][j];k++){
                    int pre = res.score;
                    int preNum = res.f[i][j];
                    int preRs=res.rs[i];
                    int preCs=res.cs[j];
                    res.f[i][j]=k;
                    calcScoreRow(res,i,max(j+1,poyo));
                    calcScoreCol(res,j,max(i+1,poyo));
                    if(res.score<=pre){
                        res.rs[i]=preRs;
                        res.cs[j]=preCs;
                        res.f[i][j]=preNum;
                        res.score = pre;
                    }
                }
            }
        }
        return res;
    }

    void calcScoreRow(State& state,int i,int bound=N){
        int res=0;
        for(auto b:B){
            int l=0,r=0;
            int sum=0;
            while(l<bound){
                while(r<bound && sum<b) sum+=state.f[i][r++];
                if(sum==b){
                    res+=b;
                    if(r==bound) break;   
                    sum+=state.f[i][r++];
                }
                if(r==bound) break;

                while(l<bound && sum>b) sum-=state.f[i][l++];
                if(sum==b){
                    res+=b;
                    sum-=state.f[i][l++];
                }
            }
        }
        state.score+=(res-state.rs[i]);
        state.rs[i]=res;
    }
    void calcScoreCol(State& state,int j,int bound=N){
        int res=0;
        for(auto b:B){
            int l=0,r=0;
            int sum=0;
            while(l<bound){
                while(r<bound && sum<b) sum+=state.f[r++][j];
                if(sum==b){
                    res+=b;
                    if(r==bound) break;
                    sum+=state.f[r++][j];
                }
                if(r==bound) break;
                while(l<bound && sum>b) sum-=state.f[l++][j];
                if(sum==b){
                    res+=b;
                    sum-=state.f[l++][j];
                }
            }
        }
        state.score+=(res-state.cs[j]);
        state.cs[j]=res;
    }
        
    score_t calcScoreNaive(State& state){
        state.score = 0;
        for(int i=0;i<N;i++) calcScoreRow(state,i);
        for(int i=0;i<N;i++) calcScoreCol(state,i);
        return state.score;
    }
    score_t calcScore(State& state){
        for(int i=0;i<2;i++){
            if(state.diffX[i]!=-1){
                calcScoreRow(state,state.diffX[i]);
                state.diffX[i]=-1;
            }
            if(state.diffY[i]!=-1){
                calcScoreCol(state,state.diffY[i]);
                state.diffY[i]=-1;
            }
        }
        return state.score;
    }
    inline int myRand(){
        return (randxor()>>1);
    }
    State getNeighbor(const State& state){
        // int nsize=1;
        State res=state;
        int wid=(myRand()%8)+1;

        int xs[2],ys[2];
        xs[0]=myRand()%(N-wid),ys[0]=myRand()%(N-wid);
        if(wid==0){
            int x=xs[0],y=ys[0];
            res.f[x][y]=myRand()%(r[x][y]-l[x][y])+l[x][y];
            res.diffX[0]=x;
            res.diffY[0]=y;
            return res;
        }
        xs[1]=xs[0]+wid,ys[1]=ys[0]+wid;
        for(auto x:xs){
            for(auto y:ys){
                res.f[x][y]=myRand()%(r[x][y]-l[x][y])+l[x][y];
            }
        }
        for(int i=0;i<2;i++) res.diffX[i]=xs[i],res.diffY[i]=ys[i];
        return res;
    };

    void reset(){};        
    static bool better(score_t lhs,score_t rhs){return lhs<rhs;};
};
