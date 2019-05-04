#include<iostream>

namespace ProconLib{
    using ll=long long;
    using Int=int;
    template<Int MOD,bool IsPrime=true>
    class ModInt{
        Int n;        
        static Int regularize(int n){Int tmp=n%MOD; return tmp>=0 ? tmp : tmp+MOD;}
        static Int regularize(ll n){Int tmp=n%MOD; return tmp>=0 ? tmp : tmp+MOD;}
        public:
        ModInt():n(0){};
        ModInt(int n):n(regularize(n)){}
        ModInt(long long n):n(regularize(n)){}
        ModInt(const ModInt<MOD,IsPrime> &mn):n(mn.n){}
        explicit operator int() const{return n;}
        explicit operator long long() const{return n;}

        ModInt<MOD,IsPrime>& operator+=(ModInt<MOD,IsPrime> rhs);
        ModInt<MOD,IsPrime>& operator-=(ModInt<MOD,IsPrime> rhs);
        ModInt<MOD,IsPrime>& operator*=(ModInt<MOD,IsPrime> rhs);

        bool operator==(ModInt<MOD,IsPrime> rhs){return n==rhs.n;}
        const Int& get() const {return n;}
        void set(int x){n=regularize(x);}
        void set(ll x){n=regularize(x);}        
    };

    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator+(ModInt<MOD,IsPrime> lhs,ModInt<MOD,IsPrime> rhs){return lhs+=rhs;};
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator+(ModInt<MOD,IsPrime> lhs,int rhs){return lhs+ModInt<MOD,IsPrime>(rhs);}
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator+(ModInt<MOD,IsPrime> lhs,ll rhs){return lhs+ModInt<MOD,IsPrime>(rhs);}
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator+(int lhs,ModInt<MOD,IsPrime> rhs){return ModInt<MOD,IsPrime>(lhs)+rhs;}
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator+(ll lhs,ModInt<MOD,IsPrime> rhs){return ModInt<MOD,IsPrime>(lhs)+rhs;}

    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator+(ModInt<MOD,IsPrime> mn){return mn;};
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator-(ModInt<MOD,IsPrime> mn){return ModInt<MOD,IsPrime>(-mn.get());};

    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator-(ModInt<MOD,IsPrime> lhs,ModInt<MOD,IsPrime> rhs){return lhs-=rhs;};
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator-(ModInt<MOD,IsPrime> lhs,int rhs){return lhs-ModInt<MOD,IsPrime>(rhs);};
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator-(ModInt<MOD,IsPrime> lhs,ll rhs){return lhs-ModInt<MOD,IsPrime>(rhs);};
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator-(int lhs,ModInt<MOD,IsPrime> rhs){return ModInt<MOD,IsPrime>(lhs)-rhs;};
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator-(ll lhs,ModInt<MOD,IsPrime> rhs){return ModInt<MOD,IsPrime>(lhs)-rhs;};

    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator*(ModInt<MOD,IsPrime> lhs,ModInt<MOD,IsPrime> rhs){return lhs*=rhs;};
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator*(ModInt<MOD,IsPrime> lhs,int rhs){return lhs*ModInt<MOD,IsPrime>(rhs);}
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator*(ModInt<MOD,IsPrime> lhs,ll rhs){return lhs*ModInt<MOD,IsPrime>(rhs);}
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator*(ll lhs,ModInt<MOD,IsPrime> rhs){return ModInt<MOD,IsPrime>(lhs)*rhs;}
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> operator*(int lhs,ModInt<MOD,IsPrime> rhs){return ModInt<MOD,IsPrime>(lhs)*rhs;}

    template<Int MOD>
    ModInt<MOD,true> operator/(ModInt<MOD,true> lhs,ModInt<MOD,true> rhs);
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> powm(ModInt<MOD,IsPrime> x,Int k);
    template<Int MOD>
    ModInt<MOD,true> inv(ModInt<MOD,true> x){return powm(x,MOD-2);}

    template<Int MOD,bool IsPrime>
    std::ostream& operator<<(std::ostream& os,const ModInt<MOD,IsPrime> &mn);
    

    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime>& ModInt<MOD,IsPrime>::operator+=(ModInt<MOD,IsPrime> rhs){
        n+=rhs.n;
        n= n>=MOD ? n-MOD : n;
        return *this;
    }
    
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime>& ModInt<MOD,IsPrime>::operator-=(ModInt rhs){
        n=n-rhs.n<0 ? n-rhs.n+MOD : n-rhs.n;
        return *this;
    }
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime>& ModInt<MOD,IsPrime>::operator*=(ModInt<MOD,IsPrime> rhs){
        n=ll(n)*rhs.n%MOD;
        return *this;
    }
    
    template<Int MOD>
    ModInt<MOD,true> operator/(ModInt<MOD,true> lhs,ModInt<MOD,true> rhs){
        return lhs*inv(rhs);
    }
    template<Int MOD,bool IsPrime>
    ModInt<MOD,IsPrime> powm(ModInt<MOD,IsPrime> x,Int k){
        ModInt<MOD,IsPrime> res(1);
        while(k){
            if(k&1) res*=x;
            k>>=1;
            x*=x;
        }
        return res;
    }

    template<Int MOD,bool IsPrime>
    std::ostream& operator<<(std::ostream& os,const ModInt<MOD,IsPrime> &mn){
        os<<mn.get();
        return os;
    }

    template<Int MOD,bool IsPrime>
    std::istream& operator>>(std::istream& is,ModInt<MOD,IsPrime> &mn){
        Int tmp;
        is>>tmp;
        mn.set(tmp);
        return is;
    }
}
