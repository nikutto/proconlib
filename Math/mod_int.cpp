#include<bits/stdc++.h>
namespace ProconLib{
    //assert not verified!!!
    using Int=int;
    using ll=long long;

    template<Int MOD,bool IsPrime =false>
    class ModInt{
        Int n;        
        public:
        ModInt():n(0){};
        ModInt(int n):n(n>=MOD ? n%MOD : (n<0 ? (n%MOD+MOD)%MOD : n)){}
        ModInt(ll n):n(n>=MOD ? n%MOD : (n<0 ? (n%MOD+MOD)%MOD : n)){}
        explicit operator int() const{return n;}
        explicit operator ll() const{return n;}

        ModInt<MOD,IsPrime>& operator+=(ModInt<MOD,IsPrime> rhs){
            n+=rhs.n;
            n= n>=MOD ? n-MOD : n;
            return *this;
        }
        ModInt<MOD,IsPrime>& operator-=(ModInt<MOD,IsPrime> rhs){
            n=n-rhs.n<0 ? n-rhs.n+MOD : n-rhs.n;
            return *this;
        }
        ModInt<MOD,IsPrime>& operator*=(ModInt<MOD,IsPrime> rhs){
            n=ll(n)*rhs.n%MOD;
            return *this;
        }
        ModInt<MOD,IsPrime> operator+(ModInt<MOD,IsPrime> rhs){
            return rhs+=*this;
        }
        ModInt<MOD,IsPrime> operator+(){
            return *this;
        }
        ModInt<MOD,IsPrime> operator-(ModInt<MOD,IsPrime> rhs){
            return rhs-=*this;
        }
        ModInt<MOD,IsPrime> operator-(){
            return ModInt<MOD,IsPrime>(-n);
        }
        ModInt<MOD,IsPrime> operator*(ModInt<MOD,IsPrime> rhs){
            return rhs*=*this;
        }
        bool operator==(ModInt<MOD,IsPrime> rhs){
            return n==rhs.n;
        }
    };


}
