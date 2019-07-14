#include<functional>
#include<string>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/tag_and_trait.hpp>
using namespace __gnu_pbds;

using key=int;
using val=std::string;

using Tree=tree<key,null_type,std::less<key>,rb_tree_tag,tree_order_statistics_node_update>;
using Map=tree<key,val,std::less<key>,rb_tree_tag,tree_order_statistics_node_update>;

int example(){
    Tree s;
    s.insert(3);
    s.insert(5);
    s.insert(6);
    s.order_of_key(5);
    s.find_by_order(1); // expected 5
    
    Map mp;
    mp[1]="one";
    mp[3]="three";
    mp[4]="four";

    mp.order_of_key(2); //means key of grater or equal to x, output is expected to be "{3,three}"'s index, 2.
    mp.find_by_order(1)->second; // i-th element, expected "three"
    return 0;
}
