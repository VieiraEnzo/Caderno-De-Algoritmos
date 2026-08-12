/**
 * Description: Ordered set e multiset usando GNU PBDS.
 *     Suporta \texttt{order\_of\_key} (rank) e \texttt{find\_by\_order} ($k$-ésimo elemento).
 * Time: $O(\log n)$ por operação
 * Status: tested
 */

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset = tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>;
