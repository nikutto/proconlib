#include<vector>
namespace ProconLib{

    //Summation only
    template<typename Int>
    struct BIT{     
        private:
        int N;
        std::vector<Int> dat;
        public:
        BIT(int N):N(N),dat(N,0){}
        void add(int pos,Int x);
        Int query(int r);
        Int query(int l,int r);
    };

    template<typename Int>
    void BIT<Int>::add(int pos,Int x){
        pos++;
        while(pos<=N){
            dat[pos-1]+=x;
            pos+=pos&-pos;
        }
    }

    template<typename Int>
    Int BIT<Int>::query(int r){
        Int res=0;
        while(r>0){
            res+=dat[r-1];
            r-=r&-r;
        }
        return res;
    }

    template<typename Int>
    Int BIT<Int>::query(int l,int r){
        return query(r)-query(l);
    }
  
};