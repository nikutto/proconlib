#include<boost/multiprecision/cpp_int.hpp>
namespace mp=boost::multiprecision;
using Int=mp::cpp_int;
using Int128=mp::int128_t;
using Int256=mp::int256_t;
using Int512=mp::int512_t;
using Int1024=mp::int1024_t;
using uInt128=mp::uint128_t;
using cint=mp::checked_int128_t;

int example(){
    mp::cpp_int n;
    std::cin>>n;

    std::string num="123";
    mp::cpp_int x(num);

    std::string s_str=x.str();
    
    return 0;
}