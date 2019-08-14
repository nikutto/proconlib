#include<vector>
#include<algorithm>
namespace ProconLib{

    namespace DetailNS{
        template<typename T>
        struct DefaultDetail{
            static bool isZero(T x){
                return x<=T(0);
            }
        };
    }
    template<typename T>
    class Polynomial{
        int N;
        std::vector<T> dat;
        
        public:
        Polynomial(int N):N(N),dat(N+1){}
        Polynomial():Polynomial(0){}
        Polynomial(const Polynomial& obj):N(obj.N),dat(obj.dat){}
        Polynomial(const Polynomial&& obj):N(obj.N),dat(std::move(obj.dat)){}

        int degree(){return N;}
        void resize(int N){ this->N=N; dat.resize(N+1,T(0));}
        template<typename Detail=DetailNS::DefaultDetail<T>>
        void shrink();
        T& operator[](int pos){return dat[pos];}
        const T& operator[](int pos) const {return dat[pos];}

        T operator()(T x);
    };

    template<typename T>
    Polynomial<T>& operator+=(Polynomial<T> &lhs,Polynomial<T> rhs);
    template<typename T>
    Polynomial<T>& operator-=(Polynomial<T> &lhs,Polynomial<T> rhs);
    template<typename T>
    Polynomial<T>& operator*=(Polynomial<T> &lhs,Polynomial<T> rhs);
    template<typename T>
    Polynomial<T>& operator*=(Polynomial<T> &lhs,T rhs);
    template<typename T>
    Polynomial<T> operator+(Polynomial<T> lhs,Polynomial<T> rhs){return lhs+=rhs;}
    template<typename T>
    Polynomial<T> operator-(Polynomial<T> lhs,Polynomial<T> rhs){return lhs-=rhs;}
    template<typename T>
    Polynomial<T> operator*(Polynomial<T> lhs,Polynomial<T> rhs){return lhs*=rhs;}
    template<typename T>
    Polynomial<T> operator*(Polynomial<T> lhs,T rhs){return lhs*=rhs;}
    template<typename T>
    Polynomial<T> operator*(T lhs,Polynomial<T> rhs){return rhs*=lhs;}

    template<typename T>
    template<typename Detail>
    void Polynomial<T>::shrink(){ 
        while(N){
            if(Detail::isZero(dat[N])) N--;
            else break;
        }
        resize(N);
    }

    template<typename T>
    Polynomial<T>& operator+=(Polynomial<T> &lhs,Polynomial<T> rhs){
        lhs.resize(std::max(lhs.degree(),rhs.degree()));
        for(int i=0;i<=rhs.degree();i++) lhs[i]+=rhs[i];
        return lhs;
    }

    template<typename T>
    Polynomial<T>& operator-=(Polynomial<T> &lhs,Polynomial<T> rhs){
        lhs.resize(std::max(lhs.degree(),rhs.degree()));
        for(int i=0;i<=rhs.degree();i++) lhs[i]-=rhs[i];
        return lhs;
    }


    template<typename T>
    Polynomial<T>& operator*=(Polynomial<T> &lhs,Polynomial<T> rhs){
        Polynomial<T> lhsTmp=lhs;
        lhs.resize(lhs.degree()+rhs.degree());
        for(int i=0;i<=lhsTmp.degree();i++) lhs[i]=T(0);
        for(int i=0;i<=lhsTmp.degree();i++){
            for(int j=0;j<=rhs.degree();j++){
                lhs[i+j]+=lhsTmp[i]*rhs[j];
            }
        }
        return lhs;
    }

    template<typename T>
    Polynomial<T>& operator*=(Polynomial<T> &lhs,T rhs){
        for(int i=0;i<=lhs.degree();i++){
            lhs[i]*=rhs;
        }
        return lhs;
    }

    template<typename T>
    Polynomial<T> operator+(Polynomial<T> poly){
        auto res=poly;
        return res;
    }

    template<typename T>
    Polynomial<T> operator-(Polynomial<T> poly){
        auto res=poly;
        for(int i=0;i<=poly.degree();i++) res[i]=-res[i];
        return res;
    }

    template<typename T>
    T Polynomial<T>::operator()(T x){
        T res=T(0);
        T px=T(1);
        for(int i=0;i<=degree();i++){
            res+=dat[i]*px;
            px*=x;
        }
        return res;
    }


}