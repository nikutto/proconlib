#include"FFT.cpp"
#include<cmath>
#include<complex>
template<typename float_t>
std::vector<float_t> convolution(std::vector<float_t> A,std::vector<float_t> B){
    using C=std::complex<float_t>;
    const float_t PI=acos(float_t(-1));
    int N=1;
    while(N<A.size()+B.size()-1) N*=2;
    std::vector<C> CA(N),CB(N);
    for(int i=0;i<A.size();i++) CA[i]=A[i];
    for(int i=0;i<B.size();i++) CB[i]=B[i];

    C w=std::polar(float_t(1),2*PI/N);
    FFT(CA,w),FFT(CB,w);
    for(int i=0;i<N;i++) CA[i]*=CB[i];

    FFT(CA,C(1)/w);
    for(int i=0;i<N;i++) CA[i]/=N;
    std::vector<float_t> res(A.size()+B.size()-1);
    for(int i=0;i<res.size();i++) res[i]=real(CA[i]);
    return res;
}
