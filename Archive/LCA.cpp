#include<bits/stdc++.h>
using namespace std;


struct Edge{
    int from,to;   
    char label;
};
using Edges=vector<Edge>;
using Graph=vector<Edges>;

namespace ProconLib{
    template<typename T>
    class LCAQuery{
        public:
        using Merger=std::function<T(T,T)>;
        using Extractor=std::function<T(Edge)>;
        private:
        int N;
        int logN;
        Merger merger;
        std::vector<std::vector<int>> par;
        std::vector<std::vector<T>> dat;
        std::vector<std::vector<T>> rev;
        std::vector<int> dep;
        void dfs(int v,int pre,const Graph& tree,Extractor& extract,Extractor& extractR);
        public:
        LCAQuery(int root,const Graph &tree,Merger merger,Extractor extract,Extractor extractR);
        LCAQuery(int root,const Graph &tree,Merger merger,Extractor extract):LCAQuery(root,tree,merger,extract,extract){};
        T query(int x,int y);
    };

    template<typename T>
    LCAQuery<T>::LCAQuery(int root,const Graph &tree,Merger merger,Extractor extract,Extractor extractR):N(tree.size()),logN(std::log2(N+1)+1),merger(merger),
                                                                            dep(N),
                                                                            par(logN,vector<int>(N)),
                                                                            dat(logN,vector<T>(N)),
                                                                            rev(logN,vector<T>(N))
    {
        par[0][root]=root;
        dfs(root,-1,tree,extract,extractR);
        for(int i=0;i+1<logN;i++){
            for(int j=0;j<N;j++){
                par[i+1][j]=par[i][par[i][j]];
                dat[i+1][j]=merger(dat[i][par[i][j]],dat[i][j]);
                rev[i+1][j]=merger(rev[i][j],rev[i][par[i][j]]);
            }
        }
    }

    template<typename T>
    void LCAQuery<T>::dfs(int v,int pre,const Graph& tree,Extractor &extract,Extractor &extractR){
        for(auto &e:tree[v]){
            if(e.to==pre) continue;
            par[0][e.to]=v;
            dat[0][e.to]=extract(e);
            rev[0][e.to]=extractR(e);
            dep[e.to]=dep[v]+1;
            dfs(e.to,v,tree,extract,extractR);
        }
    }

    template<typename T>
    T LCAQuery<T>::query(int x,int y){
        assert(0<=x && x<N && 0<=y && y<N);
        if(x==y) return T();
        bool xf=false,yf=false;
        T xDat,yDat;
        auto upperX=[&](int step){
            if(xf) xDat=merger(xDat,rev[step][x]);
            else xDat=rev[step][x],xf=true;;
            x=par[step][x];
        };
        auto upperY=[&](int step){
            if(yf) yDat=merger(dat[step][y],yDat);
            else yDat=dat[step][y],yf=true;;
            y=par[step][y];
        };
        auto ans=[&](){
            if(xf){
                if(yf) return merge(xDat,yDat);
                else return xDat;
            }
            else{
                if(yf) return yDat;
                else return T();
            }
        };
        if(dep[x]<dep[y]){
            for(int i=logN-1;i>=0;i--){
                if(dep[par[i][y]]>=dep[x]){
                    upperY(i);        
                }
            }
        }
        else if(dep[x]>dep[y]){
            for(int i=logN-1;i>=0;i--){
                if(dep[par[i][x]]>=dep[y]){
                    upperX(i);        
                }
            }
        }
        if(x==y) return ans();
        for(int i=logN-1;i>=0;i--){
            if(par[i][x]!=par[i][y]){
                upperX(i);
                upperY(i);
            }
        }
        assert(x!=y);
        upperX(0);
        upperY(0);
        assert(x==y);
        return ans();
    }
}

//verify
/*
using namespace ProconLib;
using namespace std;
string merger(string lhs,string rhs){
    return lhs+rhs;
}
string ext(Edge x){
    return string{x.label};
}
string extR(Edge x){
    return string{char(tolower(x.label))};
}
int main(){
    int n;
    cin>>n;
    Graph g(n);
    for(int i=0;i<n-1;i++){
        int p;
        cin>>p;
        g[i+1].push_back(Edge{i+1,p,'A'+i});
        g[p].push_back(Edge{p,i+1,'A'+i});
    }

    LCAQuery<string> solver(0,g,merger,ext,extR);
    int q;
    cin>>q;
    while(q--){
        int a,b;
        cin>>a>>b;
        cout<<solver.query(a,b)<<endl;
    }

    return 0;
}
*/