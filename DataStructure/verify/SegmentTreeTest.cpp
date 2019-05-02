/*verfy(AOJ DSL_2_A)*/
#include<iostream>
#include<algorithm>
#include"../SegmentTree.cpp"
using namespace ProconLib;
struct MyMonoid{
    using value_t=int;
    static constexpr value_t E(){return (1u<<31)-1;}
    static value_t op(value_t lhs,value_t rhs){return std::min(lhs,rhs);}
};

int main(){
    int n,q;
    std::cin>>n>>q;
    SegmentTree<MyMonoid> seg(n);
    for(int i=0;i<q;i++){
        int com,x,y;
        std::cin>>com>>x>>y;
        if(com){
            y++;
            std::cout<<seg.query(x,y)<<std::endl;
        }
        else{
            seg.update(x,y);
        }
    }
    return 0;
}
