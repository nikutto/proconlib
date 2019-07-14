#include<boost/multiprecision/miller_rabin.hpp>
namespace mp=boost::multiprecision;

int example(){
    mp::cpp_int n;
    int k;
    mp::miller_rabin_test(n,k);
    return 0;
}
