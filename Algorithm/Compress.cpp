#include<vector>
#include<algorithm>
#include<map>
namespace ProconLib{
    template<typename T>
    std::map<T,int> Compress(std::vector<T> v){
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        std::map<T,int> res;
        int id=0;
        for(auto &x:v){
            res[x]=id++;
        }
        return res;
    }
}