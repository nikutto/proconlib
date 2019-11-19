#include<vector>

template<typename T>
void FFT(std::vector<T>& f,T w){
    int N=f.size();
    int tmpN=1;
    while(tmpN<N) tmpN*=2;
    assert(tmpN==N);

    for(int wid=N;wid>=2;wid>>=1){
        int h=wid>>1;
        T wt = 1;
        for(int i=0;i<h;i++){
            for(int j=i;j<N;j+=wid){
                T x = f[j]-f[j+h];
                f[j]=f[j]+f[j+h];
                f[j+h]=x*wt;
            }
            wt*=w;
        }
        w=w*w;
    }
    int i=0;
    for(int j=1;j<N;j++){
        for (int k=N>>1;k>(i^=k);k>>=1);
        if (j < i) swap(f[i], f[j]);
    }
}
