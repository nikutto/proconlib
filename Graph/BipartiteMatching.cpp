#include<vector>
#include<utility>
#include"MaximumFlow.cpp"

namespace ProconLib{

    class BipartiteMatching:private MaximumFlow<int>{
        using Super=MaximumFlow<int>;
        using Super::g;
        int N,M;
        int S,T;
        int matchNum=0;
        int X(int id){return id;}
        int Y(int id){return N+id;}
        int inverseY(int id){return id-N;}
        public:
        BipartiteMatching(int N,int M);
        void addEdge(int x,int y){Super::addEdge(X(x),Y(y),1);}
        int match(){return matchNum+=maximumFlow(S,T);}
        std::vector<std::pair<int,int>> getMatches();
    };

    BipartiteMatching::BipartiteMatching(int N,int M):N(N),M(M),S(N+M),T(N+M+1),Super(N+M+2){
        for(int i=0;i<N;i++) Super::addEdge(S,X(i),1);
        for(int i=0;i<M;i++) Super::addEdge(Y(i),T,1);
    }
    std::vector<std::pair<int,int>> BipartiteMatching::getMatches(){
        std::vector<std::pair<int,int>> res;
        for(int i=0;i<N;i++){
            for(auto& e:g[X(i)]){
                if(e.to!=S && e.cap==0){
                    res.push_back(std::pair<int,int>{i,inverseY(e.to)});
                }
            }
        }
        return res;
    }
}