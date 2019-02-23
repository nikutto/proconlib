#include<bits/stdc++.h>
using namespace std;
namespace ProconLib{
    template<typename T>
    struct L{
        T a,b; //ax+b
        L():L(0,0){}
        L(T a,T b):a(a),b(b){}
        static T f(L l,T x){ return l.a*x+l.b; }
        static bool isDropMid(L l0,L l1,L l2){
            return (l2.b-l1.b)*(l1.a-l0.a)>=(l1.b-l0.b)*(l2.a-l1.a);
        }
    };
    template<typename T,typename Comp=std::less<T>>
    class ConvexHullTrick{
        std::vector<L<T>> lines;
        int head=0;
        public:
        ConvexHullTrick(){}
        void add(L<T> l){
            while(lines.size()>=2 && L<T>::isDropMid(*(lines.end()-2),lines.back(),l)){
                lines.pop_back();
                if(head>lines.size()) head=lines.size();
            }
            lines.push_back(l);
        }
        T get(T x){
            while(head+1<lines.size() && Comp()(L<T>::f(lines[head],x),L<T>::f(lines[head+1],x))){
                head++;
            }
            return L<T>::f(lines[head],x);
        }
    };
    template<typename T,typename Comp>
    void build(ConvexHullTrick<T,Comp>& cht,vector<L<T>> vec){
        sort(vec.begin(),vec.end(),Comp);
        for(auto l:vec) cht.add(l);
    }
}

/*verify mytest
using namespace ProconLib;
int main(){
    ConvexHullTrick<int> cht;
    cht.add(L<int>(0,0));
    cht.add(L<int>(1,0));
    cht.add(L<int>(2,-1));
    cht.add(L<int>(4,-8));
    for(int i=0;i<=5;i++){
        int res=cht.get(i);
        cout<<"#"<<i<<" "<<res<<endl;
    }
    return 0;
}
*/