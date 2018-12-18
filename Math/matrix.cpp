#include<bits/stdc++.h>

namespace ProconLib{
    //assert not verified!!!
    template<typename T>
    class Matrix{
        int r,c;
        std::vector<std::vector<T>> dat;
        public:
        Matrix(int r,int c):r(r),c(c),dat(r,std::vector<T>(c)){}
        Matrix(int r,int c,T x):r(r),c(c),dat(r,std::vector<T>(c,x)){}

        std::vector<T>& operator[](int pos){return dat[pos];};
        std::vector<T> const& operator[](int pos) const{return dat[pos];};
        std::vector<T>& at(int pos){return dat[pos];}
        int row_size() const {return r;}
        int col_size() const {return c;}
    };

    template<typename T>
    Matrix<T> operator+(const Matrix<T>& lhs,const Matrix<T>& rhs){
        assert(lhs.row_size()==rhs.row_size() && lhs.col_size()==rhs.col_size());
        int r=lhs.row_size(),c=lhs.col_size();
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
        assert(lhs.row_size()==rhs.row_size() && lhs.col_size()==rhs.col_size());
        int r=lhs.row_size(),c=lhs.col_size();
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
        int r=mat.row_size(),c=mat.col_size();
        Matrix<T> res(r,c);
        for(int i=0;i<r;i++)for(int j=0;j<c;j++) res[i][j]=-mat[i][j];
        return res;
    }
    template<typename T>
    Matrix<T> operator-(const Matrix<T>& mat){
        int r=mat.row_size(),c=mat.col_size();
        Matrix<T> res(r,c);
        for(int i=0;i<r;i++)for(int j=0;j<c;j++) res[i][j]=-mat[i][j];
        return res;
    }
    
    template<typename T>
    Matrix<T> operator*(const Matrix<T>& lhs,const Matrix<T> &rhs){
        assert(lhs.col_size()==rhs.row_size());
        int r=lhs.row_size(),c=rhs.col_size(),l=lhs.col_size();
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
        assert(mat.row_size()==mat.col.size());
        Matrix<T> x=mat;
        Matrix<T> res=Identity(mat.row_size());
        while(k){
            if(k&1) res*=x;
            x=x*x;
            k>>=1;
        }
        return res;
    }

}