
// CPP program for above approach
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
typedef pair<int, int> Interval;
 
// An invalid interval, used as
// return value to denote that no
// matching interval was found
const Interval NO_INTERVAL_FOUND = { 1, 0 };
 
// interval update policy struct
template <class Node_CItr,
          class Node_Itr,
          class Cmp_Fn, class _Alloc>
struct interval_node_update_policy {
 
    // Our metadata is maximum of
    // right-endpoints of intervals in the
    // sub-tree, which is of type int
    typedef int metadata_type;
 
    // An utility function to check
    // if given two intervals overlap
    bool doOverlap(Interval i1,
                   Node_CItr i2)
    {
        return (i1.first <= (*i2)->second
                && (*i2)->first <= i1.second);
    }
 
    // Search for any interval that
    // overlaps with Interval i
    Interval overlapSearch(Interval i)
    {
        for (Node_CItr it = node_begin();
             it != node_end();) {
            if (doOverlap(i, it)) {
                return { (*it)->first,
                         (*it)->second };
            }
 
            if (it.get_l_child() != node_end()
                && it.get_l_child()
                           .get_metadata()
                       >= i.first) {
                it = it.get_l_child();
            }
            else {
                it = it.get_r_child();
            }
        }
        return NO_INTERVAL_FOUND;
    }
 
    // To restore the node-invariance
    // of the node pointed to by
    // (it). We need to derive the
    // metadata for node (it) from
    // its left-child and right-child.
    void operator()(Node_Itr it,
                    Node_CItr end_it)
    {
        int max_high = (*it)->second;
 
        if (it.get_l_child() != end_it) {
            max_high = max(
                max_high,
                it.get_l_child()
                    .get_metadata());
        }
 
        if (it.get_r_child() != end_it) {
            max_high = max(
                max_high,
                it.get_r_child()
                    .get_metadata());
        }
 
        // The max of right-endpoint
        // of this node and the max
        // right-endpoints of children.
        const_cast<int&>(
            it.get_metadata())
            = max_high;
    }
 
    virtual Node_CItr node_begin() const = 0;
    virtual Node_CItr node_end() const = 0;
    virtual ~interval_node_update_policy() {}
};
 
// IntervalTree data structure
// rb_tree_tag: uses red-black search tree
// interval_node_update_policy:
// our custom Node_update policy
typedef tree<Interval,
             null_type,
             less<Interval>,
             rb_tree_tag,
             interval_node_update_policy>
    IntervalTree;
 
// Driver Code
int main()
{
    IntervalTree IT;
    Interval intvs[] = { { 15, 20 },
                         { 10, 30 },
                         { 17, 19 },
                         { 5, 20 },
                         { 12, 15 },
                         { 30, 40 } };
 
    for (Interval intv : intvs) {
        IT.insert(intv);
    }
 
    Interval toSearch = { 25, 29 };
    cout << "\nSearching for interval ["
         << toSearch.first << ", "
         << toSearch.second << "]";
    Interval res = IT.overlapSearch(toSearch);
    if (res == NO_INTERVAL_FOUND)
        cout << "\nNo Overlapping Interval\n";
    else
        cout << "\nOverlaps with ["
             << res.first << ", "
             << res.second << "]\n";
 
    Interval toErase = { 10, 30 };
    IT.erase(toErase);
    cout << "\nDeleting interval ["
         << toErase.first << ", "
         << toErase.second
         << "]\n";
 
    cout << "\nSearching for interval ["
         << toSearch.first << ", "
         << toSearch.second << "]";
    res = IT.overlapSearch(toSearch);
    if (res == NO_INTERVAL_FOUND)
        cout << "\nNo Overlapping Interval\n";
    else
        cout << "\nOverlaps with ["
             << res.first << ", "
             << res.second << "]\n";
    return 0;
}
