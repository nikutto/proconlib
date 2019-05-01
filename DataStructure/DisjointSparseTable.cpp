#include<bits/stdc++.h>

namespace ProconLib{

    template<typename T,class Merge>
    class DisjointSparseTable{
        const int logN;
        const int N;
        const int clzN;
        std::vector<std::vector<T>> ldat;
        std::vector<std::vector<T>> rdat;
        std::vector<T> dat;

        Merge merge;
        static int calcN(int n){
            int v=1;
            int res=0;
            while(v<n){
                v*=2;
                res++;
            }
            return res;
        }
        void build(int k,int l,int r){
            if(r-l<=1) return;
            int len=r-l;
            int mid=(l+r)/2;
            int halfLen=mid-l;
            ldat[k].resize(halfLen); //[l,mid)
            ldat[k][0]=dat[mid-1];
            for(int i=1;i<halfLen;i++){
                if(dat.size()<=mid-i-1) break;
                ldat[k][i]=merge(dat[mid-i-1],ldat[k][i-1]);
            }
            rdat[k].resize(halfLen); //[mid,r)
            rdat[k][0]=dat[mid];
            for(int i=1;i<halfLen;i++){
                if(dat.size()<=mid+i) break;
                rdat[k][i]=merge(rdat[k][i-1],dat[mid+i]);
            }
            build(k*2+1,l,mid);
            build(k*2+2,mid,r);
        }
        public:
        DisjointSparseTable(const std::vector<T>& vec,Merge merge=Merge()):logN(calcLogN(vec.size())),N(1<<logN),clzN(__builtin_clz(N)),ldat(N-1),rdat(N-1),dat(vec),merge(merge){
            build(0,0,N);
        };
        T query(int l,int r){ //[l,r)
            r--;
            if(l==r) return dat[l];
            int dep =__builtin_clz(l^r)-clzN-1;
            int p=l>>(logN-dep);
            int id=(1<<dep)-1+p;
            int lb=p<<(logN-dep);
            int ub=(p+1)<<(logN-dep);
            int mid=(lb+ub)/2;
            return merge(ldat[id][mid-l-1],rdat[id][r-mid]);
        }
    };
};