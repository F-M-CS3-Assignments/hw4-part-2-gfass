#include "bdc.h"
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Converts a vector of integers to a string representation
string vec_to_string(vector<int> v) {
    string result = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        result += to_string(v[i]);
        if (i != v.size() - 1) result += ", ";
    }
    result += "]";
    return result;
}

/*
 * Helper function to find the largest divisible subset using dynamic programming.
 * This function qualifies as dynamic programming because:
 * - It uses a bottom-up table-based approach to store solutions to subproblems.
 * - Each entry in the DP table (dp[i]) stores the length of the longest
 *   divisible subset ending at index i.
 * - It uses a separate array (prev) to track the previous index in the subset chain
 *   for easy reconstruction of the final result.
 */
vector<int> findLargestDivisibleSubset(vector<int> input) {
    if (input.empty()) return {};

    // Save a copy of the original input to track output order later
    vector<int> original = input;

    // Step 1: Sort the input list in ascending order
    // This ensures that for any pair (a, b) with a < b, I can easily check divisibility
    sort(input.begin(), input.end());

    int n = input.size();

    // -------------------- DYNAMIC PROGRAMMING BEGINS HERE --------------------

    // dp[i] stores the length of the longest valid divisible subset ending at input[i]
    // This acts as the DP table storing solutions to subproblems
    vector<int> dp(n, 1);

    // prev[i] stores the index of the previous element in the subset ending at input[i]
    // Used to reconstruct the subset after computing its length
    vector<int> prev(n, -1);

    int maxIndex = 0; // Tracks the index where the largest subset ends

    /*
     * Time Complexity Comparison:
     *
     * Previous Approach (Recursive without memoization):
     * - In the worst case, every number can be either included or excluded in a conglomerate,
     *   leading to a time complexity of O(2^n), where n is the size of the input list.
     * - This is exponential time and becomes inefficient for larger inputs.
     *
     * Current Approach (Dynamic Programming):
     * - Sort the input list: O(n log n)
     * - Nested loops to build the DP table: O(n^2)
     * - Subset reconstruction: O(n)
     * - Overall time complexity: O(n^2)
     *   → significantly more efficient than the recursive solution.
     */

    // Step 2: Fill the DP table (bottom-up approach)
    // For each input[i], check all previous elements input[j] (j < i)
    // If input[i] is divisible by input[j], can consider extending the chain ending at j
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (input[i] % input[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j; // Record where this optimal path came from
            }
        }
        // Update maxIndex if this is the longest chain found so far
        if (dp[i] > dp[maxIndex]) {
            maxIndex = i;
        }
    }

    // Step 3: Reconstruct the subset by walking backward through prev[]
    vector<int> subset;
    for (int i = maxIndex; i >= 0; i = prev[i]) {
        subset.push_back(input[i]);
        if (prev[i] == -1) break;
    }

    return subset; // This is correct in value, but not in original input order
}

// Main function to find the biggest divisible conglomerate
vector<int> biggest_divisible_conglomerate(vector<int> input) {
    if (input.empty()) return {};

    // Step 1: Get the largest divisible subset using the DP-based helper
    vector<int> subset = findLargestDivisibleSubset(input);

    // Step 2: Restore the output order to match reverse appearance in original input
    // This is required by the assignment spec (to match expected output format)
    vector<int> orderedResult;
    for (int i = input.size() - 1; i >= 0; --i) {
        if (find(subset.begin(), subset.end(), input[i]) != subset.end()) {
            orderedResult.push_back(input[i]);
        }
    }

    return orderedResult;
}