using namespace __gnu_pbds; 
using namespace std;
 
typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
 
void myerase(ordered_set &t, int v){
    int rank = t.order_of_key(v);//Number of elements that are less than v in t
    ordered_set::iterator it = t.find_by_order(rank); //Iterator that points to the (rank+1)th element in t
    t.erase(it);
}
