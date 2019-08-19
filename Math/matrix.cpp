#include<vector>
#include<iostream>
#include<cassert>

namespace ProconLib{
    
    template<typename T>
    struct Detail{
        static constexpr T EPS = T(1e-9);
        static bool isZero(T v){
            return abs(v)<=EPS;
        }
    };

    template<typename T>
    class Vector{
        int N;
        std::vector<T> dat;
        public:
        Vector(int n):N(n),dat(n){}
        Vector(int n,T x):N(n),dat(n,x){}
        Vector(std::vector<T> vec):N(vec.size()),dat(vec){}
        Vector(const std::vector<T>& vec):N(vec.size()),dat(vec){}
        Vector(const Vector& vec){dat=vec.dat;}
        int size() const {return N;}
        T& operator[](int pos){return dat[pos];};
        const T& operator[](int pos) const{return dat[pos];};
        T& at(int pos){return dat.at(pos);}
        const T& at(int pos) const {return dat.at(pos);}
    };
    
    template<typename T>
    class Matrix{
        int r,c;
        std::vector<Vector<T>> dat;
        public:
        Matrix(int r,int c):r(r),c(c),dat(r,Vector<T>(c)){}
        Matrix(int r,int c,T x):r(r),c(c),dat(r,Vector<T>(c,x)){}

        Vector<T>& operator[](int pos){return dat[pos];};
        const Vector<T>& operator[](int pos) const{return dat[pos];};
        Vector<T>& at(int pos){return dat.at(pos);}
        const Vector<T>& at(int pos) const {return dat.at(pos);}
        int rowSize() const {return r;}
        int colSize() const {return c;}
    };
    template<typename T>
    Matrix<T> operator+(const Matrix<T>& lhs,const Matrix<T>& rhs);
    template<typename T>
    Matrix<T> operator-(const Matrix<T>& lhs,const Matrix<T>& rhs);
    template<typename T>
    Matrix<T> operator+(const Matrix<T>& mat);
    template<typename T>
    Matrix<T> operator-(const Matrix<T>& mat);
    template<typename T>
    Matrix<T> operator*(const Matrix<T>& lhs,const Matrix<T> &rhs);
    template<typename T>
    Matrix<T> Identity(int n);
    template<typename T>
    Matrix<T> pow(const Matrix<T>& mat,int k);
    template<typename T,typename Detail=Detail<T>>
    Matrix<T> gaussianElimination(Matrix<T> mat);
    template<typename T>
    int rank(const Matrix<T>& mat);
    template<typename T>
    Matrix<T> inv(const Matrix<T>& mat);
    template<typename T>
    Vector<T> operator*(const Matrix<T>& lhs,const Vector<T> &rhs);


    
    template<typename T>
    Matrix<T> operator+(const Matrix<T>& lhs,const Matrix<T>& rhs){
        assert(lhs.rowSize()==rhs.rowSize() && lhs.colSize()==rhs.colSize());
        int r=lhs.rowSize(),c=lhs.colSize();
        Matrix<T> res(r,c);
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                res[i][j]=lhs[i]+rhs[i];
            }
        }
        return res;
    }
    template<typename T>
    Matrix<T> operator-(const Matrix<T>& lhs,const Matrix<T>& rhs){
        assert(lhs.rowSize()==rhs.rowSize() && lhs.colSize()==rhs.colSize());
        int r=lhs.rowSize(),c=lhs.colSize();
        Matrix<T> res(r,c);
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                res[i][j]=lhs[i]-rhs[i];
            }
        }
        return res;
    }
    template<typename T>
    Matrix<T> operator+(const Matrix<T>& mat){
        int r=mat.rowSize(),c=mat.colSize();
        Matrix<T> res(r,c);
        for(int i=0;i<r;i++)for(int j=0;j<c;j++) res[i][j]=-mat[i][j];
        return res;
    }
    template<typename T>
    Matrix<T> operator-(const Matrix<T>& mat){
        int r=mat.rowSize(),c=mat.colSize();
        Matrix<T> res(r,c);
        for(int i=0;i<r;i++)for(int j=0;j<c;j++) res[i][j]=-mat[i][j];
        return res;
    }
    
    template<typename T>
    Matrix<T> operator*(const Matrix<T>& lhs,const Matrix<T> &rhs){
        assert(lhs.colSize()==rhs.rowSize());
        int r=lhs.rowSize(),c=rhs.colSize(),l=lhs.colSize();
        Matrix<T> res(r,c);
        for(int i=0;i<r;i++){
            for(int k=0;k<l;k++){
                for(int j=0;j<c;j++){
                    res[i][j]+=lhs[i][k]*rhs[k][j];
                }
            }
        }
        return res;
    }

    template<typename T>
    Matrix<T> Identity(int n){
        assert(n>=0);
        Matrix<T> res(n,n);
        for(int i=0;i<n;i++){
            res[i][i]=1;
        }
        return res;
    }

    template<typename T>
    Matrix<T> pow(const Matrix<T>& mat,int k){
        assert(mat.rowSize()==mat.colSize());
        Matrix<T> x=mat;
        Matrix<T> res=Identity<T>(mat.rowSize());
        while(k){
            if(k&1) res=res*x;
            x=x*x;
            k>>=1;
        }
        return res;
    }
    
    template<typename T,typename Detail=Detail<T>>
    Matrix<T> gaussianElimination(Matrix<T> mat){
        int m=mat.rowSize(),n=mat.colSize();
        int row=0;
        for(int j=0;j<n;j++){
            if(row==m) break;
            int tar=-1;
            T v=Detail::EPS;
            for(int i=row;i<m;i++){
                if(!Detail::isZero(mat[i][j]) && abs(v)<abs(mat[i][j])){
                    tar=i;
                    v=mat[i][j];
                }
            }
            if(tar==-1) continue;
            if(row!=tar){ 
                auto tmp=mat[row];
                mat[row]=mat[tar];
                mat[tar]=tmp;
            }
            for(int i=row+1;i<m;i++){
                if(!Detail::isZero(mat[i][j])){
                    T r=mat[i][j]/mat[row][j];
                    for(int k=j;k<n;k++){
                        mat[i][k]-=r*mat[row][k];
                    }
                }
            }
            row++;
        }
        return mat;
    }

    template<typename T,typename Detail=Detail<T>>
    int rank(const Matrix<T>& mat){
        auto tmp=gaussialElimination(mat);
        int m=tmp.rowSize(),n=tmp.colSize();
        int i=0,j=0;
        while(i<m && j<n){
            if(Detail::isZero(tmp[i][j])) j++;
            else i++,j++;
        }
        return i;
    }

    template<typename T>
    Matrix<T> inv(const Matrix<T>& mat){
        assert(mat.rowSize()==mat.colSize());
        int n=mat.rowSize();
        Matrix<T> tmp(n,2*n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                tmp[i][j]=mat[i][j];
                tmp[i][j+n]=0;
            }
            tmp[i][i+n]=1;
        }
        mat=gaussianElimination(mat);
        Matrix<T> res(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                res[i][j]=mat[i][j+n]/=mat[i][i];
            }
        }
        return res;
    }
 
    template<typename T>
    void debug(Matrix<T> mat){
        int m=mat.rowSize(),n=mat.colSize();
        std::cerr<<"###Matrix_Debug###"<<std::endl;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                std::cerr<<mat[i][j]<<" ";
            }
            std::cerr<<std::endl;
        }
    }

    template<typename T>
    Vector<T> operator*(const Matrix<T>& lhs,const Vector<T> &rhs){
        assert(lhs.colSize()==rhs.size());
        int m=lhs.rowSize(),n=rhs.size();
        Vector<T> res(m);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                res[i]+=lhs[i][j]*rhs[j];
            }
        }
        return res;
    }

}