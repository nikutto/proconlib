#include<vector>
#include<string>
#include<queue>

namespace ProconLib{
    
    template<class Language>
    class AhoCorasick{
        public:
        using char_t=typename Language::char_t;
        using string_t=typename Language::string_t;

        private:
        using Edges=std::vector<int>;
        using Graph=std::vector<Edges>;

        private:
        Language lang;
        int N,C;
        Graph g;
        std::vector<int> _failure;
        std::vector<int> _accept;
        void add(int id,const string_t& pat);

        public:
        AhoCorasick(std::vector<string_t> patterns,Language lang=Language());
        int getRoot(){return 0;}
        int rejectToken(){return -1;}
        int size(){return N;}
        int next(int v,char_t x){return g[v][lang.id_of(x)]; }
        int failure(int v){return _failure[v];}
        int accept(int v){return _accept[v];}
    };

    template<class Language>
    void AhoCorasick<Language>::add(int id,const string_t& pat){
        int v=0;
        for(auto& c:pat){
            int to=g[v][lang.id_of(c)];
            if(to==0){
                to=N++;
                g.push_back(Edges(C,0));
                _accept.push_back(rejectToken());
                g[v][lang.id_of(c)]=to;
            }
            v=to;
        }
        _accept[v]=id;
    }

    template<class Language>
    AhoCorasick<Language>::AhoCorasick(std::vector<string_t> patterns,Language lang)
        :lang(lang),C(lang.size()),N(1),g(1,Edges(C)),_accept(1,rejectToken()),_failure(1,0)
    {
        int id=0;
        for(auto &pat:patterns){
            add(id++,pat);
        }
        _failure.assign(N,0);

        struct T3{int pre,label,v;};
        std::queue<T3> que;
        que.push(T3{0,-1,0});
        
        while(!que.empty()){
            T3 st=que.front(); que.pop();
            if(st.pre!=0){
                _failure[st.v]=g[_failure[st.pre]][st.label];
                _accept[st.v]=max(_accept[st.v],_accept[_failure[st.v]]);
            }
            for(int i=0;i<C;i++) if(g[st.v][i]!=0) que.push(T3{st.v,i,g[st.v][i]});
            for(int i=0;i<C;i++) if(g[st.v][i]==0) g[st.v][i]=g[_failure[st.v]][i];
        }
    }

    // example
    struct LowerCase{
        using char_t=char;
        using string_t=std::string;
        constexpr int size(){return 26;}
        int id_of(char x){return x-'a';}
    };

}