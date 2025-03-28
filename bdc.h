

#include <vector>
#include <string>


using namespace std;


// Although pass by reference would probably be more efficient
// for one or both of these methods, it is not a substantial difference
// since the vectors used in this program are not very large.
string vec_to_string(vector<int> v);
vector<int> biggest_divisible_conglomerate(vector<int> input);



