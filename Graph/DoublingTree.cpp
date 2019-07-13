#include"LCA.cpp"

namespace ProconLib{

    // requirement
    // graph_t g: g[i][j]:Edge
    //      struct Edge{
    //          int to;
    //          value_t val;                
    //      }

    template<class graph_t,class Monoid>
    class TreeDoubling:public LCA<graph_t>{
        public:
        using Super=LCA<graph_t>;
        using value_t=typename Monoid::value_t;
        using Super::N;
        using Super::logN;
        using Super::par;

        protected:
        std::vector<std::vector<value_t>> dat;
        public:
        TreeDoubling(int root,const graph_t& g);
        int lca(int a,int b){return Super::query(a,b);}
        value_t query(int a,int t);
    };

    template<class graph_t,class Monoid>
    TreeDoubling<graph_t,Monoid>::TreeDoubling(int root,const graph_t& g):  Super(root,g),
                                                                            dat(logN,std::vector<value_t>(N))
    {
        for(int i=0;i<N;i++){
            if(i==root){
                dat[0][i]=Monoid::E();
                continue;
            }
            for(auto &e:g[i]){
                if(par[i]==e.to){
                    dat[0][i]=e.val;
                }
            }
        }
        for(int i=0;i+1<N;i++){
            for(int j=0;j<N;j++){
                dat[i+1][j]=Monoid::op(dat[i][j],dat[i][par[i][j]]);
            }
        }
    }

    template<class graph_t,class Monoid>
    typename TreeDoubling<graph_t,Monoid>::value_t TreeDoubling<graph_t,Monoid>::query(int a,int t){
        value_t res=Monoid::E();
        for(int i=logN-1;i>=0;i--){
            if((t>>i)&1){
                res=Monoid::op(res,dat[i][a]);
                a=par[i][a];
            }
        }
        return res;
    }

}