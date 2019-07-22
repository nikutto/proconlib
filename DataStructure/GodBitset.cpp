#include<cmath>
#include<valarray>

namespace ProconLib{

    
    // To commit Zuru
    class GodBitset{
        public:
        using Int=long long;    
        static constexpr size_t SIZE=sizeof(Int);
        static constexpr size_t LOG_SIZE=std::log2(SIZE);

        private:
        const int N;
        const int DatSize;
        protected:
        std::valarray<Int> dat;
        GodBitset(size_t N,std::valarray<Int> dat):N(N),DatSize((N+SIZE-1)/SIZE),dat(dat){}
        public:
        GodBitset(size_t N):N(N),DatSize((N+SIZE-1)/SIZE),dat(DatSize,0){}
        
        GodBitset operator~() const {return GodBitset(N,~dat);}
        GodBitset& operator&=(const GodBitset& rhs){dat&=rhs.dat; return *this;}
        GodBitset& operator|=(const GodBitset& rhs){dat|=rhs.dat; return *this;}
        GodBitset& operator^=(const GodBitset& rhs){dat^=rhs.dat; return *this;}
        GodBitset& operator>>(int d){
            int diff=d>>LOG_SIZE;
            int offset=d&((1<<LOG_SIZE)-1);
            for(int i=0;i<N;i++){
                dat[i]=
            }
        }        

    };

    GodBitset operator&(const GodBitset& lhs,const GodBitset& rhs){auto tmp=lhs; return tmp&=rhs;}
    GodBitset operator|(const GodBitset& lhs,const GodBitset& rhs){auto tmp=lhs; return tmp|=rhs;}
    GodBitset operator^(const GodBitset& lhs,const GodBitset& rhs){auto tmp=lhs; return tmp^=rhs;}
}

int main(){
    return 0;
}